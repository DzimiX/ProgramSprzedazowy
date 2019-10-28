#include "entrywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    entryWindow w;
    w.show();
    return a.exec();
}
