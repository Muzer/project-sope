#include "panel.h"
#include "ui_panel.h"

Panel::Panel(QWidget *parent, QString path)
    : QWidget(parent), ui(new Ui::Panel)
{
    ui->setupUi(this);
    this->resize(48, 48);
    desktop_path = path;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    project_name = "Project Sope"; // FIXME use /etc/sope/system.xml
    this->setToolTip(tr(QString("This is the main application launcher for " + project_name).toStdString().c_str()));
}

Panel::~Panel()
{
    delete ui;
}

void Panel::move_panel(int x, int y)
{
    this->move(x, y);
}
