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

void Panel::move_panel(int x, int y)
{
    this->move(x, y);
}
