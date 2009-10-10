#include <QtGui/QApplication>
#include "background.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Background background;
    background.show();
    return a.exec();
}
