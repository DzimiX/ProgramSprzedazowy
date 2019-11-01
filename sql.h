#ifndef SQL_H
#define SQL_H

#include <QtSql>
#include <QFileInfo>
#include <QtDebug>
#include <QString>

class sql
{
public:
    QSqlDatabase db;
    bool dbOpen(void);
    void dbClose(void);
    void dbCreate(QString location);
};

#endif // SQL_H
