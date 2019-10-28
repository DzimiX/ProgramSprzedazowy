#include "productswindow.h"
#include "ui_productswindow.h"

productsWindow::productsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::productsWindow)
{
    ui->setupUi(this);
}

productsWindow::~productsWindow()
{
    delete ui;
}
