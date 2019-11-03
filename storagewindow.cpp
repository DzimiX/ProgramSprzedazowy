#include "storagewindow.h"
#include "ui_storagewindow.h"

storageWindow::storageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::storageWindow)
{
    ui->setupUi(this);
}

storageWindow::~storageWindow()
{
    delete ui;
}
