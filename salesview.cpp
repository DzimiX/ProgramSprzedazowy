#include "salesview.h"
#include "ui_salesview.h"

salesView::salesView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesView)
{
    ui->setupUi(this);
}

salesView::~salesView()
{
    delete ui;
}

void salesView::on_button_return_clicked()
{
    salesView::close();
}
