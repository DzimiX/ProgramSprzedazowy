#ifndef PRODUCTSWINDOW_H
#define PRODUCTSWINDOW_H

#include <QDialog>
#include "editproducts.h"

namespace Ui {
class productsWindow;
}

class productsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit productsWindow(QWidget *parent = nullptr);
    ~productsWindow();

private slots:
    void on_button_addNew_clicked();

    void on_button_editSelected_clicked();

    void on_button_removeSelected_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked();

private:
    Ui::productsWindow *ui;
public:
    void updateProductList();
};

#endif // PRODUCTSWINDOW_H
