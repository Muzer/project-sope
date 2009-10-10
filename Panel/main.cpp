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
#include <QtGui/QApplication>
#include "panel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget desktop;
    Panel panel1;
    Panel panel2("/usr/share/applications/panel_2", PANEL_POSITION_BR);
    // FIXME get list of applications from ~/.sope/panel_settings.xml
    // FIXME get panels, panel positions and screen numbers from
    // ~/.sope/panel_settings.xml

    return a.exec();
}
