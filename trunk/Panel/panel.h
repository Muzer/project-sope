#ifndef PANEL_H
#define PANEL_H

#include <QDesktopWidget>
#include <QtGui/QWidget>
#include <QtOpenGL/QGLWidget>

namespace Ui
{
    class Panel;
}

class Panel : public QWidget
{
    Q_OBJECT

public:
    Panel(QWidget *parent = 0, QString path = "/usr/share/applications/panel_1/"); // FIXME get list of applications from ~/.sope/default_applications.xml
    ~Panel();
    void move_panel(int x, int y);

private:
    Ui::Panel *ui;
    QString desktop_path;
    QString project_name;
};

#endif // PANEL_H
