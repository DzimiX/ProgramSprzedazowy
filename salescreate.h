#ifndef SALESCREATE_H
#define SALESCREATE_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QDateTime>
#include <QObject>
#include "sql.h"

namespace Ui {
class salesCreate;
}

class salesCreate : public QDialog
{
    Q_OBJECT

public slots:
    void createInvoice(QString clientName);

public:
    explicit salesCreate(QWidget *parent = nullptr);
    ~salesCreate();
    void updateDetails();

private slots:
    void on_button_quit_clicked();

    void on_pushButton_clicked();

private:
    Ui::salesCreate *ui;
};

#endif // SALESCREATE_H
