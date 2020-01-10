#ifndef SQL_H
#define SQL_H

#include <QtSql>
#include <QFileInfo>
#include <QtDebug>
#include <QString>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QTextTable>
#include <QDate>
#include <QDateTime>

class sql
{
public:
    QString location = "C:/db/test.db";
    QSqlDatabase db;
    bool dbOpen(QString location);
    void dbClose(void);
    void dbCreate(QString location);
    bool dbExists(QString location);
    void printInvoice(int invoiceId);
};

#endif // SQL_H
