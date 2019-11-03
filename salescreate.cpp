#include "salescreate.h"
#include "ui_salescreate.h"

salesCreate::salesCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesCreate)
{
    ui->setupUi(this);
}

salesCreate::~salesCreate()
{
    delete ui;
}

void salesCreate::on_button_quit_clicked()
{
    salesCreate::close();
}
