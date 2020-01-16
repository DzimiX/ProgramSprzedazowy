#ifndef SALESCREATE_H
#define SALESCREATE_H

#include "sql.h"
#include "salesappenditem.h"

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
    void fillCombo();

private slots:
    void on_button_quit_clicked();
    void on_button_cancel_clicked();
    void on_button_addElement_clicked();
    void on_tableView_clicked();
    void on_button_removeElement_clicked();

    void on_button_print_clicked();

private:
    Ui::salesCreate *ui;
};

#endif // SALESCREATE_H
