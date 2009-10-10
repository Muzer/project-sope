#include <QtGui/QApplication>
#include "surface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Surface surface;
    surface.show();
    return a.exec();
}
