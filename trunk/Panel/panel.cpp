#include "panel.h"

Panel::Panel(QWidget *parent, QString path)
{
    this->resize(48, 48);
    desktop_path = path;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
    project_name = "Project Sope"; // FIXME use /etc/sope/system.xml
    this->setToolTip("This is the main application launcher for " + project_name);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    QPainter painter;
}

Panel::~Panel()
{
}

void Panel::move_panel(int x, int y)
{
    this->move(x, y);
}

void Panel::paint_rectangle(QPainter &painter){
    QBrush brush(QColor(255, 255, 0, 255));
    painter.setBrush(brush);
    painter.drawRoundedRect(1, 1, this->width() - 2, this->height() - 2, 20, 15);
}

void Panel::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    paint_rectangle(painter);
    painter.end();
}
