#ifndef SQL_H
#define SQL_H

#include <QtSql>
#include <QFileInfo>
#include <QtDebug>
#include <QString>

class sql
{
public:
    QString location = "C:/db/test.db";
    QSqlDatabase db;
    bool dbOpen(QString location);
    void dbClose(void);
    void dbCreate(QString location);
    bool dbExists(QString location);
};

#endif // SQL_H
