//----------------------------------------------------------------------
// Surface - the shape drawer for Project Sope
// Copyright (C) 2009 Melon Development Team
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------
#include "surface.h"

Surface::Surface(QWidget *parent, int screen_no)
{
    QDesktopWidget desktop;
    int x, y, w, h;
    QRect g = desktop.availableGeometry(screen_no);
    g.getRect(&x, &y, &w, &h);
    this->resize(w, h);
    this->move(x, y);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    Display *dpy = QX11Info::display(); // Remove taskbar button. NOTE This is
    // what breaks Windows compatibility
    Atom net_wm_state_skip_taskbar=XInternAtom(dpy,
        "_NET_WM_STATE_SKIP_TASKBAR", False);
    Atom net_wm_state = XInternAtom(dpy, "_NET_WM_STATE", False);
    XChangeProperty(dpy, winId(), net_wm_state,
        XA_ATOM, 32, PropModeAppend,
        (unsigned char *)&net_wm_state_skip_taskbar, 1);
}
