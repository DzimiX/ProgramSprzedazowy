#include "entrywindow.h"

#include <QGuiApplication>
#include <QApplication>
#include <QtSql>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtTranslator; //qtTransalator for Yes / No transalation in dialog boxes
    if (qtTranslator.load(QLocale::system(),
                "qt", "_",
                QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
        a.installTranslator(&qtTranslator);
    }

    QTranslator qtBaseTranslator;
    if (qtBaseTranslator.load("qtbase_" + QLocale::system().name(),
                QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
        a.installTranslator(&qtBaseTranslator);
    }

    a.setQuitOnLastWindowClosed(false);
    entryWindow w;
    w.show();

    return a.exec();
}
