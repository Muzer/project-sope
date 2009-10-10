#include "background.h"

Background::Background(QWidget *parent, int screen_no)
{
    QDesktopWidget desktop;
    int x, y, w, h;
    QRect g = desktop.availableGeometry(screen_no);
    g.getRect(&x, &y, &w, &h);
    this->resize(w, h);
    this->move(x, y);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint);
    Display *dpy = QX11Info::display(); // Remove taskbar button. NOTE This is
    // what breaks Windows compatibility
    Atom net_wm_state_skip_taskbar=XInternAtom(dpy,
        "_NET_WM_STATE_SKIP_TASKBAR", False);
    Atom net_wm_state = XInternAtom(dpy, "_NET_WM_STATE", False);
    XChangeProperty(dpy, winId(), net_wm_state,
        XA_ATOM, 32, PropModeAppend,
        (unsigned char *)&net_wm_state_skip_taskbar, 1);
}
