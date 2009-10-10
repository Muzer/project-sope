#ifndef SURFACE_H
#define SURFACE_H

#include <QGLWidget>
#include <QtGui/QDesktopWidget>
#include <QtGui/QPainter>

class Surface : public QGLWidget
{
    Q_OBJECT

public:
    Surface(QWidget *parent = 0, int screen_no = -1);
};

#endif // SURFACE_H
