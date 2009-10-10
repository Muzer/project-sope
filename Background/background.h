#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGLWidget>
#include <QtGui/QDesktopWidget>
#include <QtGui/QPainter>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <QX11Info>

class Background : public QGLWidget
{
    Q_OBJECT

public:
    Background(QWidget *parent = 0, int screen_no = -1);
};

#endif // BACKGROUND_H
