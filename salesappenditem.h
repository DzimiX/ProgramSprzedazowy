#ifndef SALESAPPENDITEM_H
#define SALESAPPENDITEM_H

#include <QDialog>
#include "sql.h"

namespace Ui {
class salesAppendItem;
}

class salesAppendItem : public QDialog
{
    Q_OBJECT

public slots:
    void appendTo(int invoiceId);

public:
    explicit salesAppendItem(QWidget *parent = nullptr);
    ~salesAppendItem();

public:
    void fillComboBox();
    void refreshStaticText();

private slots:
    void on_comboBox_activated();

    void on_button_return_clicked();

    void on_button_add_clicked();

private:
    Ui::salesAppendItem *ui;
};

#endif // SALESAPPENDITEM_H
