#ifndef SQL_H
#define SQL_H

#include <QtSql>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>

class sql
{
public:
    QString location = qApp->applicationDirPath()+"/db/baza.db";
    QSqlDatabase db;
    bool dbOpen(QString location);
    void dbClose(void);
    void dbCreate(QString location);
    bool dbExists(QString location);
    void dbCreatePdf(int invoiceId);
};

#endif // SQL_H
