#include "editproducts.h"
#include "ui_editproducts.h"

editProducts::editProducts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editProducts)
{
    ui->setupUi(this);
}

editProducts::~editProducts()
{
    delete ui;
}
