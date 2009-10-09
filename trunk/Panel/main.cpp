#include <QtGui/QApplication>
#include "panel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget desktop;
    Panel panel1;
    Panel panel2(0, "/usr/share/applications/panel_2", PANEL_POSITION_BR); // FIXME get list of applications from ~/.sope/panel_settings.xml
    // FIXME get panels, panel positions and screen numbers from ~/.sope/panel_settings.xml

    return a.exec();
}
