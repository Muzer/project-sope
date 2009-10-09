#include <QtGui/QApplication>
#include "panel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Panel panel1;
    Panel panel2(0, "/usr/share/applications/panel_2"); // FIXME get list of applications from ~/.sope/default_applications.xml
    QDesktopWidget desktop;
    int x, y, w, h;
    QRect g = desktop.availableGeometry(desktop.primaryScreen());
    g.getRect(&x, &y, &w, &h);
    panel1.move_panel(x, y);
    panel1.show();
    panel2.move_panel((x + w) - panel2.width(), (y + h) - panel2.height());
    panel2.show();
    return a.exec();
}
