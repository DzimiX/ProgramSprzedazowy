#ifndef SQL_H
#define SQL_H

#include <QtSql>
#include <QFileInfo>
#include <QtDebug>

class sql
{
public:
    QSqlDatabase db;
    bool dbOpen(void);
    void dbClose(void);
};

#endif // SQL_H
