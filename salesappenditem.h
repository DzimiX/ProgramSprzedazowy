#ifndef SALESAPPENDITEM_H
#define SALESAPPENDITEM_H

#include <QMessageBox>

#include "sql.h"

namespace Ui {
class salesAppendItem;
}

class salesAppendItem : public QDialog
{
    Q_OBJECT

public:
    explicit salesAppendItem(QWidget *parent = nullptr);
    ~salesAppendItem();
    static int invoiceId;
    static int customerId;
public:
    void fillComboBox();
    void updateDetails();
    int productAmount(int id);

private slots:
    void on_comboBox_activated();
    void on_button_return_clicked();
    void on_button_add_clicked();

private:
    Ui::salesAppendItem *ui;
};

#endif // SALESAPPENDITEM_H
