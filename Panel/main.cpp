#include <QtGui/QApplication>
#include "panel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Panel panel1;
    Panel panel2(0, "/usr/share/applications/panel_2");
    panel1.move_panel(0, 0);
    panel1.show();
    QDesktopWidget desktop;
    int x, y, w, h;
    QRect g = desktop.availableGeometry();
    g.getRect(&x, &y, &w, &h);
    panel2.move_panel(w - 48, h - 48);
    panel2.show();
    return a.exec();
}
