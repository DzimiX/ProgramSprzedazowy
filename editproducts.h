#ifndef EDITPRODUCTS_H
#define EDITPRODUCTS_H

#include <QDialog>

namespace Ui {
class editProducts;
}

class editProducts : public QDialog
{
    Q_OBJECT

public slots:
    void reciveProductId( int id );

public:
    explicit editProducts(QWidget *parent = nullptr);
    ~editProducts();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::editProducts *ui;
};

#endif // EDITPRODUCTS_H
