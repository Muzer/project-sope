#include "panel.h"




Panel::Panel(QWidget *parent, QString path, int position, int screen_no)
{
    this->resize(48, 48); // FIXME: Set width to the number of applications.
    QDesktopWidget desktop;
    int x, y, w, h;
    QRect g = desktop.availableGeometry(screen_no);
    g.getRect(&x, &y, &w, &h); // Get top-left x, top-left y, width and height
    // of screen screen_no
    if (position == PANEL_POSITION_TL) this->move_panel(x, y);
    if (position == PANEL_POSITION_TR) this->move_panel((x + w) -
        this->width(), y);
    if (position == PANEL_POSITION_BL) this->move_panel(x, (y + h) -
        this->height());
    if (position == PANEL_POSITION_BR) this->move_panel((x + w) - this->width(),
        (y + h) - this->height());
    // Depending on the panel position, place it accordingly.
    desktop_path = path;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );

    Display *dpy = QX11Info::display(); // Remove taskbar button. NOTE This is
    // what breaks Windows compatibility
    Atom net_wm_state_skip_taskbar=XInternAtom(dpy,
        "_NET_WM_STATE_SKIP_TASKBAR", False);
    Atom net_wm_state = XInternAtom(dpy, "_NET_WM_STATE", False);
    XChangeProperty(dpy, winId(), net_wm_state,
        XA_ATOM, 32, PropModeAppend,
        (unsigned char *)&net_wm_state_skip_taskbar, 1);

    project_name = "Project Sope"; // FIXME use /etc/sope/system.xml
    this->setToolTip("This is the main application launcher for " +
        project_name);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    /*    this->setAttribute(Qt::WA_TranslucentBackground, true); */
    // The above is not needed or wanted in any way shape or form. In fact, the
    // one above that isn't needed in my setup but let's keep it anyway, it
    // doesn't do harm
    QPainter painter;
    this->show();
}

Panel::~Panel()
{
}

void Panel::move_panel(int x, int y)
{
    this->move(x, y);
}

void Panel::paint_rectangle(QPainter &painter)
{
    int roundness(96);
    QRect widget_rect = this->rect();

    painter.save();

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::red);

    // clip
    QPainterPath rounded_rect;
    rounded_rect.addRoundRect(0, 0, widget_rect.width(),
        widget_rect.height(), roundness, roundness);
    painter.setClipPath(rounded_rect);

    // get clipping region
    QRegion maskregion = painter.clipRegion();

    // mask the widget
    setMask(maskregion);

    // fill path with color
    painter.fillPath(rounded_rect,QBrush(QColor(255,255,0,255)));
    // FIXME: Get colour from colours.xml

    // restore painter
    painter.restore();
}

void Panel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    paint_rectangle(painter);
}
