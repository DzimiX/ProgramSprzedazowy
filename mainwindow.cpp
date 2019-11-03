#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow() :
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    updateStaticText();
}

mainWindow::~mainWindow()
{
    delete ui;
    QApplication::quit();
}

void mainWindow::on_pushButton_clicked()
{
    salesWindow salesWindow;
    salesWindow.setModal(true);
    salesWindow.exec();
}

void mainWindow::on_pushButton_2_clicked()
{
    suppliesWindow suppliesWindow;
    suppliesWindow.setModal(true);
    suppliesWindow.exec();
}

void mainWindow::on_pushButton_3_clicked()
{
    clientsWindow clientsWindow;
    clientsWindow.setModal(true);
    clientsWindow.exec();
}

void mainWindow::on_pushButton_4_clicked()
{
    productsWindow productsWindow;
    productsWindow.setModal(true);
    productsWindow.exec();
}

void mainWindow::on_pushButton_5_clicked()
{
    companyWindow companyWindow;
    companyWindow.setModal(true);
    companyWindow.exec();
    updateStaticText();
}

void mainWindow::updateStaticText(){
    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from firma");
    query->exec();

    query->seek(-1);
    query->next();
    ui->company_name->setText(query->value(0).toString());

    conn.dbClose();
}
