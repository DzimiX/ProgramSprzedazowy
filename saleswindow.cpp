#include "saleswindow.h"
#include "ui_saleswindow.h"

salesWindow::salesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesWindow)
{
    ui->setupUi(this);
}

salesWindow::~salesWindow()
{
    delete ui;
}
