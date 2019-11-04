#ifndef ADDPRODUCTS_H
#define ADDPRODUCTS_H

#include <QDialog>
#include "sql.h"

namespace Ui {
class addProducts;
}

class addProducts : public QDialog
{
    Q_OBJECT

public:
    explicit addProducts(QWidget *parent = nullptr);
    ~addProducts();

private slots:
    void on_button_add_clicked();
    void on_button_return_clicked();

private:
    Ui::addProducts *ui;
};

#endif // ADDPRODUCTS_H
