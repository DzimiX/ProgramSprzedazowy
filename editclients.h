#ifndef EDITCLIENTS_H
#define EDITCLIENTS_H

#include <QDialog>

namespace Ui {
class editClients;
}

class editClients : public QDialog
{
    Q_OBJECT

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
