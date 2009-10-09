#ifndef PANEL_H
#define PANEL_H

#include <QGLWidget>
#include <QtGui/QDesktopWidget>
#include <QtGui/QPainter>

class Panel : public QGLWidget
{
    Q_OBJECT

public:
    Panel(QWidget *parent = 0, QString path = "/usr/share/applications/panel_1/"); // FIXME get list of applications from ~/.sope/default_applications.xml);
    ~Panel();
    void move_panel(int x, int y);

private:
    QString desktop_path;
    QString project_name;

protected:
    void paintEvent();
};

#endif // PANEL_H
