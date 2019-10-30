#ifndef PRODUCTSWINDOW_H
#define PRODUCTSWINDOW_H

#include <QDialog>

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

private:
    Ui::productsWindow *ui;
private:
    void updateProductList();
};

#endif // PRODUCTSWINDOW_H
