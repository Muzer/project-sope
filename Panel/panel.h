//----------------------------------------------------------------------
// Panel - The panel for Project Sope
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
#ifndef PANEL_H
#define PANEL_H

#include <QGLWidget>
#include <QtGui/QDesktopWidget>
#include <QtGui/QPainter>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <QX11Info>

enum { PANEL_POSITION_TL, PANEL_POSITION_TR, PANEL_POSITION_BL,
    PANEL_POSITION_BR };

class Panel : public QGLWidget
{
    Q_OBJECT

public:
    Panel(QString path =
        "/usr/share/applications/panel_1/", int position = PANEL_POSITION_TL,
        int screen_no = -1);
    // FIXME get list of applications from ~/.sope/panel_settings.xml);
    ~Panel();
    void move_panel(int x, int y);


private:
    QString desktop_path;
    QString project_name;
    void paint_rectangle(QPainter &painter);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PANEL_H
