#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGLWidget>
#include <QtGui/QDesktopWidget>
#include <QtGui/QPainter>

class Background : public QGLWidget
{
    Q_OBJECT

public:
    Background(QWidget *parent = 0, int screen_no = -1);
};

#endif // BACKGROUND_H
