#ifndef PANEL_H
#define PANEL_H

#include <QGLWidget>
#include <QtGui/QDesktopWidget>
#include <QtGui/QPainter>

enum { PANEL_POSITION_TL, PANEL_POSITION_TR, PANEL_POSITION_BL, PANEL_POSITION_BR };

class Panel : public QGLWidget
{
    Q_OBJECT

public:
    Panel(QWidget *parent = 0, QString path = "/usr/share/applications/panel_1/", int position = PANEL_POSITION_TL, int screen_no = -1); // FIXME get list of applications from ~/.sope/default_applications.xml);
    ~Panel();
    void move_panel(int x, int y);


private:
    QString desktop_path;
    QString project_name;
    void paint_rectangle(QPainter &painter);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PANEL_H
