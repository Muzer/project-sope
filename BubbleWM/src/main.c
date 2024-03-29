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

#include <glib.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include <libgnomeui/libgnomeui.h>

#include "maximus-app.h"

static gboolean on_sess_save (GnomeClient        *client,
                              gint                arg1, 
                              GnomeSaveStyle      arg2,
                              gboolean            arg3,
                              GnomeInteractStyle  arg4,
                              gboolean            arg5);

static gboolean no_restart = FALSE;
static gboolean version    = FALSE;
gboolean no_maximize = FALSE;

GOptionEntry entries[] = 
{
 {
   "no-restart", 's', 
   0, G_OPTION_ARG_NONE, 
   &no_restart, 
   "Do not automatically restart (standalone)", NULL 
 },
 {
   "version", 'v', 
   0, G_OPTION_ARG_NONE, 
   &version, 
   "Prints the version number", NULL 
 },
 {
   "no-maximize", 'm',
   0, G_OPTION_ARG_NONE,
   &no_maximize,
   "Do not automatically maximize every window", NULL
 },
 { 
   NULL 
 }
};gint
main (gint argc, gchar *argv[])
{
  MaximusApp *app;
  GnomeClient *client;
  GOptionContext  *context;
  gchar *exec[] = {"maximus"};

  g_thread_init (NULL);
  g_set_application_name ("Maximus");
  
  gtk_init (&argc, &argv);

  context = g_option_context_new ("- Maximus");
  g_option_context_add_main_entries (context, entries, "maximus");
  g_option_context_add_group (context, gtk_get_option_group (TRUE));
  g_option_context_parse (context, &argc, &argv, NULL);
  g_option_context_free(context);  
  
  if (!no_restart)
  {
    gnome_program_init ("maximus", "0.3", LIBGNOMEUI_MODULE, argc, argv,
                        GNOME_PARAM_NONE, NULL);

    client = gnome_master_client ();
    gnome_client_set_restart_command (client, 1, exec);
    gnome_client_set_restart_style (client, GNOME_RESTART_IMMEDIATELY);

    g_signal_connect (client, "save-yourself", 
                      G_CALLBACK (on_sess_save), NULL);
  }

  gdk_error_trap_push ();
  app = maximus_app_get_default ();
  gdk_error_trap_pop ();

  gtk_main ();

  return EXIT_SUCCESS;
}

static gboolean on_sess_save (GnomeClient        *client,
                              gint                arg1, 
                              GnomeSaveStyle      arg2,
                              gboolean            arg3,
                              GnomeInteractStyle  arg4,
                              gboolean            arg5)
{
  return TRUE;
}
