#include "panel.h"

Panel::Panel(QWidget *parent, QString path)
{
    this->resize(48, 48);
    desktop_path = path;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    project_name = "Project Sope"; // FIXME use /etc/sope/system.xml
    this->setToolTip("This is the main application launcher for " + project_name);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
}

Panel::~Panel()
{
}

void Panel::move_panel(int x, int y)
{
    this->move(x, y);
}

void Panel::paintEvent()
{
    QBrush brush(QColor(255, 255, 0, 255));
    QPainter painter(this);
    painter.setBrush(brush);
    painter.drawRoundRect(1, 1, 46, 46);
}
