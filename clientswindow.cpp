#include "clientswindow.h"
#include "ui_clientswindow.h"

clientsWindow::clientsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientsWindow)
{
    ui->setupUi(this);
}

clientsWindow::~clientsWindow()
{
    delete ui;
}
