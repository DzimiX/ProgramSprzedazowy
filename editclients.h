#ifndef EDITCLIENTS_H
#define EDITCLIENTS_H

#include "sql.h"

namespace Ui {
class editClients;
}

class editClients : public QDialog
{
    Q_OBJECT

public slots:
    void reciveClientId( int id );

public:
    explicit editClients(QWidget *parent = nullptr);
    ~editClients();

private slots:
    void on_button_update_clicked();
    void on_button_return_clicked();

private:
    Ui::editClients *ui;
};

#endif // EDITCLIENTS_H
