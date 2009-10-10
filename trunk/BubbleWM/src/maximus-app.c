/*
 * Copyright (C) 2008 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as 
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by Neil Jagdish Patel <neil.patel@canonical.com>
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include <gconf/gconf.h>
#include <gconf/gconf-client.h>

#include "maximus-app.h"
#include "maximus-bind.h"
#include "xutils.h"

G_DEFINE_TYPE (MaximusApp, maximus_app, G_TYPE_OBJECT);

#define MAXIMUS_APP_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj),\
  MAXIMUS_TYPE_APP, \
  MaximusAppPrivate))

/* Gconf keys */
#define APP_PATH                   "/apps/maximus"
#define APP_EXCLUDE_CLASS APP_PATH "/exclude_class"
#define APP_UNDECORATE    APP_PATH "/undecorate"
#define APP_NO_MAXIMIZE   APP_PATH "/no_maximize"

/* A set of default exceptions */
static gchar *default_exclude_classes[] = 
{
  "Apport-gtk",
  "Bluetooth-properties",
  "Bluetooth-wizard",
  "Download", /* Firefox Download Window */
  "Ekiga",
  "Extension", /* Firefox Add-Ons/Extension Window */
  "Gcalctool",
  "Gimp",
  "Global", /* Firefox Error Console Window */
  "Gnome-dictionary",
  "Gnome-launguage-selector",
  "Gnome-nettool",
  "Gnome-volume-control",
  "Kiten",
  "Kmplot",
  "Nm-editor",
  "Pidgin",
  "Polkit-gnome-authorization",
  "Update-manager",
  "Skype",
  "Toplevel", /* Firefox "Clear Private Data" Window */
  "Transmission"
};

struct _MaximusAppPrivate
{
  MaximusBind *bind;
  WnckScreen *screen;

  GSList *exclude_class_list;
  gboolean undecorate;
  gboolean no_maximize;
};

static GQuark was_decorated = 0;

/* <TAKEN FROM GDK> */
typedef struct {
    unsigned long flags;
    unsigned long functions;
    unsigned long decorations;
    long input_mode;
    unsigned long status;
} MotifWmHints, MwmHints;

#define MWM_HINTS_FUNCTIONS     (1L << 0)
#define MWM_HINTS_DECORATIONS   (1L << 1)
#define _XA_MOTIF_WM_HINTS		"_MOTIF_WM_HINTS"

static gboolean
wnck_window_is_decorated (WnckWindow *window)
{
  GdkDisplay *display = gdk_display_get_default();
  Atom hints_atom = None;
  guchar *data;
  MotifWmHints *hints = NULL;
  Atom type;
  gint format;
  gulong nitems;
  gulong bytes_after;
  gboolean retval;
  
  hints_atom = gdk_x11_get_xatom_by_name_for_display (display, 
                                                      _XA_MOTIF_WM_HINTS);

  XGetWindowProperty (GDK_DISPLAY_XDISPLAY (display), 
                      wnck_window_get_xid (window),
		                  hints_atom, 0, sizeof (MotifWmHints)/sizeof (long),
		                  False, AnyPropertyType, &type, &format, &nitems,
		                  &bytes_after, &data);
  
  hints = (MotifWmHints *)data; 
  
  if (type == None)
    retval = TRUE;
  else
  {
	
//    if (hints->flags & MWM_HINTS_DECORATIONS)
  //  {
    //  hints->flags |= MWM_HINTS_DECORATIONS;
      retval = hints->decorations;
   // }
  }
  
  XFree (hints);
  return retval;
}

static void
gdk_window_set_mwm_hints (WnckWindow *window,
			                    MotifWmHints *new_hints)
{
  GdkDisplay *display = gdk_display_get_default();
  Atom hints_atom = None;
  guchar *data;
  MotifWmHints *hints;
  Atom type;
  gint format;
  gulong nitems;
  gulong bytes_after;
  
  hints_atom = gdk_x11_get_xatom_by_name_for_display (display, 
                                                      _XA_MOTIF_WM_HINTS);

  XGetWindowProperty (GDK_DISPLAY_XDISPLAY (display), 
                      wnck_window_get_xid (window),
		                  hints_atom, 0, sizeof (MotifWmHints)/sizeof (long),
		                  False, AnyPropertyType, &type, &format, &nitems,
		                  &bytes_after, &data);
  
  if (type == None)
    hints = new_hints;
  else
  {
    hints = (MotifWmHints *)data;
	
    if (new_hints->flags & MWM_HINTS_FUNCTIONS)
    {
      hints->flags |= MWM_HINTS_FUNCTIONS;
      hints->functions = new_hints->functions;  
    }
    if (new_hints->flags & MWM_HINTS_DECORATIONS)
    {
      hints->flags |= MWM_HINTS_DECORATIONS;
      hints->decorations = new_hints->decorations;
    }
  }
  
  gdk_error_trap_push ();
  XChangeProperty (GDK_DISPLAY_XDISPLAY (display), wnck_window_get_xid (window),
                   hints_atom, hints_atom, 32, PropModeReplace,
                   (guchar *)hints, sizeof (MotifWmHints)/sizeof (long));
  gdk_flush ();
  gdk_error_trap_pop ();
  
  if (hints != new_hints)
    XFree (hints);
}

static void
_window_set_decorations (WnckWindow      *window,
			                   GdkWMDecoration decorations)
{
  MotifWmHints hints;
  
  g_return_if_fail (WNCK_IS_WINDOW (window));
  
  /* initialize to zero to avoid writing uninitialized data to socket */
  memset(&hints, 0, sizeof(hints));
  hints.flags = MWM_HINTS_DECORATIONS;
  hints.decorations = decorations;
 
  gdk_window_set_mwm_hints (window, &hints);
}

/* </TAKEN FROM GDK> */

gboolean
window_is_too_large_for_screen (WnckWindow *window)
{
  static GdkScreen *screen = NULL;
  gint x=0, y=0, w=0, h=0;

  if (screen == NULL)
    screen = gdk_screen_get_default ();

  wnck_window_get_geometry (window, &x, &y, &w, &h);
  if (w > (gdk_screen_get_width (screen) + 20) //some wiggle room
      || h > (gdk_screen_get_height (screen)+20))
  {
    return TRUE;
  }
  return FALSE;
}

static void
on_window_state_changed (WnckWindow      *window,
                         WnckWindowState  change_mask,
                         WnckWindowState  new_state,
                         MaximusApp     *app)
{
  g_return_if_fail (WNCK_IS_WINDOW (window));

  if (GPOINTER_TO_INT (g_object_get_data (G_OBJECT (window), "exclude"))==1)
    return;

  if (change_mask & WNCK_WINDOW_STATE_MAXIMIZED_HORIZONTALLY
      || change_mask & WNCK_WINDOW_STATE_MAXIMIZED_VERTICALLY)
  {
    if (wnck_window_is_maximized (window) && app->priv->undecorate)
    {
      if (window_is_too_large_for_screen (window))
      {
        /* The window is too big for the screen, so redecorate */
        _window_set_decorations (window, 1);
        wnck_window_unmaximize (window);
      }
      else
      {    
        _window_set_decorations (window, 0);
      }
    }
    else
    {
      _window_set_decorations (window, 1);
    }
  }
}

static gboolean
is_excluded (MaximusApp *app, WnckWindow *window)
{
  MaximusAppPrivate *priv;
  WnckClassGroup *group;
  WnckWindowType type;
  WnckWindowActions actions;
  gchar *res_name;
  gchar *class_name;
  GSList *c;
  gint i;

  g_return_val_if_fail (MAXIMUS_IS_APP (app), TRUE);
  g_return_val_if_fail (WNCK_IS_WINDOW (window), TRUE);
  priv = app->priv;

  type = wnck_window_get_window_type (window);
  if (type != WNCK_WINDOW_NORMAL)
    return TRUE;

  if (GPOINTER_TO_INT (g_object_get_data (G_OBJECT (window), "exclude"))==1)
    return TRUE;
  
  group = wnck_window_get_class_group (window);
  
  _wnck_get_wmclass (wnck_window_get_xid (window), &res_name, &class_name);

  g_debug ("Window opened: res_name=%s -- class_name=%s", res_name, class_name);

  /* Ignore if the window is already fullscreen */
  if (wnck_window_is_fullscreen (window))
  {
    g_debug ("Excluding (is fullscreen): %s\n",wnck_window_get_name (window));
    return TRUE;
  }

  /* Make sure the window supports maximising */
  actions = wnck_window_get_actions (window);
  if (actions & WNCK_WINDOW_ACTION_RESIZE
      && actions & WNCK_WINDOW_ACTION_MAXIMIZE_HORIZONTALLY 
      && actions & WNCK_WINDOW_ACTION_MAXIMIZE_VERTICALLY
      && actions & WNCK_WINDOW_ACTION_MAXIMIZE)
    ; /* Is good to maximise */
  else
    return TRUE;
 
  /* Check internal list of class_ids */
  for (i = 0; i < G_N_ELEMENTS (default_exclude_classes); i++)
  {
    if ((class_name && default_exclude_classes[i] 
        && strstr (class_name, default_exclude_classes[i]))
        || (res_name && default_exclude_classes[i] && strstr (res_name, 
                                            default_exclude_classes[i])))
    {
      g_debug ("Excluding: %s\n", wnck_window_get_name (window));
      return TRUE;
    } 
  }
  
  /* Check user list */
  for (c = priv->exclude_class_list; c; c = c->next)
  {
    if ((class_name && c->data && strstr (class_name, c->data))
        || (res_name && c->data && strstr (res_name, c->data) ))
    {
      g_debug ("Excluding: %s\n", wnck_window_get_name (window));
      return TRUE;
    }
  }

  g_free (res_name);
  g_free (class_name);
  return FALSE;
}

extern gboolean no_maximize;

static void
on_window_opened (WnckScreen  *screen, 
                  WnckWindow  *window,
                  MaximusApp *app)
{ 
  MaximusAppPrivate *priv;
  WnckWindowType type;
  gint exclude = 0;
  
  g_return_if_fail (MAXIMUS_IS_APP (app));
  g_return_if_fail (WNCK_IS_WINDOW (window));
  priv = app->priv;

  type = wnck_window_get_window_type (window);
  if (type != WNCK_WINDOW_NORMAL)
    return;

  /* Ignore undecorated windows */
  exclude = wnck_window_is_decorated (window) ? 0 : 1;
  if (wnck_window_is_maximized (window))
    exclude = 0;
  g_object_set_data (G_OBJECT (window), "exclude", GINT_TO_POINTER (exclude));

  if (is_excluded (app, window))
  {
    g_signal_connect (window, "state-changed",
                      G_CALLBACK (on_window_state_changed), app);
    return;
  }

  if (no_maximize || priv->no_maximize)
  {
    if (wnck_window_is_maximized(window))
    {
      _window_set_decorations (window, 0);
      gdk_flush ();
    }
    g_signal_connect (window, "state-changed",
                      G_CALLBACK (on_window_state_changed), app);
    return;
  }

  if (priv->undecorate)
  {
    /* Only undecorate right now if the window is smaller than the screen */
    if (!window_is_too_large_for_screen (window))
    {
      _window_set_decorations (window, 0);
      gdk_flush ();
    }
  }

  wnck_window_maximize (window);

  g_signal_connect (window, "state-changed",
                    G_CALLBACK (on_window_state_changed), app);
}

static void
on_app_no_maximize_changed (GConfClient *client,
                            guint cid,
                            GConfEntry *entry,
                            MaximusApp *app)
{
  MaximusAppPrivate *priv;
  GConfValue* value;

  g_return_if_fail (MAXIMUS_IS_APP (app));
  priv = app->priv;

  if (entry == NULL) 
  {
    priv->no_maximize = FALSE;
  }
  else
  {
    value = gconf_entry_get_value(entry);
    priv->no_maximize = value != NULL && gconf_value_get_bool(value);
  }
}

/* GConf Callbacks */
static void
on_exclude_class_changed (GConfClient        *client,
                          guint               cid,
                          GConfEntry         *entry,
                          MaximusApp         *app)
{
  MaximusAppPrivate *priv;
  
  g_return_if_fail (MAXIMUS_IS_APP (app));
  priv = app->priv;

  g_slist_free (priv->exclude_class_list);
  
  priv->exclude_class_list= gconf_client_get_list (client, 
                                                   APP_EXCLUDE_CLASS, 
                                                   GCONF_VALUE_STRING,
                                                   NULL);
}

static gboolean
show_desktop (WnckScreen *screen)
{
  wnck_screen_toggle_showing_desktop (screen, TRUE);
  return FALSE;
}

static void
on_app_undecorate_changed (GConfClient        *client,
                           guint               cid,
                           GConfEntry         *entry,
                           MaximusApp         *app)
{
  MaximusAppPrivate *priv;
  GList *windows, *w;
    
  g_return_if_fail (MAXIMUS_IS_APP (app));
  priv = app->priv;

  priv->undecorate = gconf_client_get_bool (client, 
                                            APP_UNDECORATE, 
                                            NULL);
  g_debug ("%s\n", priv->undecorate ? "Undecorating" : "Decorating");
  
  windows = wnck_screen_get_windows (priv->screen);
  for (w = windows; w; w = w->next)
  {
    WnckWindow *window = w->data;

    if (!WNCK_IS_WINDOW (window))
      continue;

    if (no_maximize || priv->no_maximize)
    {
      if (!wnck_window_is_maximized(window))
        continue;
    }

    if (!is_excluded (app, window))
    {
      gdk_error_trap_push ();
      _window_set_decorations (window, priv->undecorate ? 0 : 1);
      wnck_window_unmaximize (window);
      wnck_window_maximize (window);
      gdk_flush ();
      gdk_error_trap_pop ();

      sleep (1);
    }
  }
  /* We want the user to be left on the launcher/desktop after switching modes*/
  g_timeout_add_seconds (1, (GSourceFunc)show_desktop, priv->screen);
}


/* GObject stuff */
static void
maximus_app_class_init (MaximusAppClass *klass)
{
  GObjectClass        *obj_class = G_OBJECT_CLASS (klass);

  g_type_class_add_private (obj_class, sizeof (MaximusAppPrivate));
}

static void
maximus_app_init (MaximusApp *app)
{
  MaximusAppPrivate *priv;
  GConfClient *client = gconf_client_get_default ();
  WnckScreen *screen;
	
  priv = app->priv = MAXIMUS_APP_GET_PRIVATE (app);

  priv->bind = maximus_bind_get_default ();

  was_decorated = g_quark_from_static_string ("was-decorated");

  gconf_client_add_dir (client, APP_PATH, GCONF_CLIENT_PRELOAD_NONE, NULL);

  priv->exclude_class_list= gconf_client_get_list (client, 
                                                   APP_EXCLUDE_CLASS, 
                                                   GCONF_VALUE_STRING,
                                                   NULL);
  gconf_client_notify_add (client, APP_EXCLUDE_CLASS,
                           (GConfClientNotifyFunc)on_exclude_class_changed,
                           app, NULL, NULL);

  priv->undecorate = gconf_client_get_bool(client, 
                                           APP_UNDECORATE, 
                                           NULL);
  gconf_client_notify_add (client, APP_UNDECORATE,
                           (GConfClientNotifyFunc)on_app_undecorate_changed,
                           app, NULL, NULL);

 
  priv->screen = screen = wnck_screen_get_default ();
  g_signal_connect (screen, "window-opened",
                    G_CALLBACK (on_window_opened), app);

  priv->no_maximize = gconf_client_get_bool(client,
                                            APP_NO_MAXIMIZE,
                                            NULL);
  g_print ("no maximize: %s\n", priv->no_maximize ? "true" : "false");
  gconf_client_notify_add (client, APP_NO_MAXIMIZE,
                           (GConfClientNotifyFunc)on_app_no_maximize_changed,
                           app, NULL, NULL);
}

MaximusApp *
maximus_app_get_default (void)

{
  static MaximusApp *app = NULL;

  if (!app)
    app = g_object_new (MAXIMUS_TYPE_APP, 
                        NULL);

  return app;
}
