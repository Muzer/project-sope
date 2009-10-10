#include "surface.h"

Surface::Surface(QWidget *parent, int screen_no)
{
    QDesktopWidget desktop;
    int x, y, w, h;
    QRect g = desktop.availableGeometry(screen_no);
    g.getRect(&x, &y, &w, &h);
    this->resize(w, h);
    this->move(0, 0);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}
