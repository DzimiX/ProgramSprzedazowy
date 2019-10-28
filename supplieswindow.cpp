#include "supplieswindow.h"
#include "ui_supplieswindow.h"

suppliesWindow::suppliesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::suppliesWindow)
{
    ui->setupUi(this);
}

suppliesWindow::~suppliesWindow()
{
    delete ui;
}
