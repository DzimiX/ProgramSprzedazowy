#include "entrywindow.h"
#include "ui_entrywindow.h"
#include "sql.h"

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
    sql sql;
    if(!sql.dbExists(sql.location)){
        sql.dbCreate(sql.location);
    }
    hide();
    mainWindow = new class mainWindow();
    this->setWindowState(Qt::WindowMinimized);
    mainWindow->setWindowFlags(Qt::Window);
    mainWindow->show();
}
