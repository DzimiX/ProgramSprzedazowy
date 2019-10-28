#include "entrywindow.h"

#include <QGuiApplication>
#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    entryWindow w;
    w.show();

    return a.exec();
}
