#ifndef EDITPRODUCTS_H
#define EDITPRODUCTS_H

#include <QDialog>

namespace Ui {
class editProducts;
}

class editProducts : public QDialog
{
    Q_OBJECT

public:
    explicit editProducts(QWidget *parent = nullptr);
    ~editProducts();

private:
    Ui::editProducts *ui;
};

#endif // EDITPRODUCTS_H
