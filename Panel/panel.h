#ifndef PANEL_H
#define PANEL_H

#include <QGLWidget>
#include <QtGui/QDesktopWidget>

class Panel : public QGLWidget
{
    Q_OBJECT

public:
    Panel(QWidget *parent = 0, QString path = "/usr/share/applications/panel_1/"); // FIXME get list of applications from ~/.sope/default_applications.xml);
    void move_panel(int x, int y);

private:
    QString desktop_path;
    QString project_name;
};

#endif // PANEL_H
