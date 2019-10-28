#include "companywindow.h"
#include "ui_companywindow.h"

companyWindow::companyWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::companyWindow)
{
    ui->setupUi(this);
}

companyWindow::~companyWindow()
{
    delete ui;
}
