#include "productswindow.h"
#include "ui_productswindow.h"
#include "sql.h"
#include <QtSql>
#include <QtDebug>

productsWindow::productsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::productsWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    updateProductList();
}

productsWindow::~productsWindow()
{
    delete ui;
}

void productsWindow::updateProductList(){
    sql conn;
    QSqlQueryModel *modal = new QSqlQueryModel;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from produkty");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    conn.dbClose();
}

void productsWindow::on_button_addNew_clicked()
{
    QString name = ui->input_name->text();
    QString unit = ui->input_unit->text();
    float price = ui->input_price->text().toFloat();
    int tax = ui->input_tax->text().toInt();

    //qDebug() << "Name: " << name << " Unit: " << unit << " Price: " << price << " Tax: " << tax; //ok

    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);
    //query->prepare("select * from produkty");
    //query->exec();
    query->prepare("insert into produkty (nazwa, jednostka, cena, vat) VALUES (:nazwa, :jednostka, :cena, :vat);");
    query->bindValue(":nazwa", name);
    query->bindValue(":jednostka", unit);
    query->bindValue(":cena", price);
    query->bindValue(":vat", tax);
    query->exec();
    //qDebug() << query;
    conn.dbClose();

    updateProductList();
}
