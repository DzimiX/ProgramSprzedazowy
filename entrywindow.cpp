#include "entrywindow.h"
#include "ui_entrywindow.h"

entryWindow::entryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::entryWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

entryWindow::~entryWindow()
{
    delete ui;
    QApplication::quit();
}


void entryWindow::on_pushButton_clicked()
{
    hide();
    mainWindow = new class mainWindow(this);
    mainWindow->show();
}
