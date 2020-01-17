#ifndef ADDCLIENTS_H
#define ADDCLIENTS_H

#include <QDialog>

#include "sql.h"

namespace Ui {
class addClients;
}

class addClients : public QDialog
{
    Q_OBJECT

public:
    explicit addClients(QWidget *parent = nullptr);
    ~addClients();

private slots:
    void on_button_add_clicked();
    void on_button_return_clicked();

private:
    Ui::addClients *ui;
};

#endif // ADDCLIENTS_H
