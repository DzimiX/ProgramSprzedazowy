#include "addproducts.h"
#include "ui_addproducts.h"

addProducts::addProducts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addProducts)
{
    ui->setupUi(this);
}

addProducts::~addProducts()
{
    delete ui;
}

void addProducts::on_button_add_clicked()
{
    QString name = ui->input_name->text();
    QString unit = ui->input_unit->text();
    double price = ui->input_price->text().toDouble();
    int tax = ui->input_tax->text().toInt();

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("insert into produkty (nazwa, jednostka, cena, vat) values (:nazwa, :jednostka, :cena, :vat)");
    //qDebug() << query;
    query->bindValue(":nazwa", name);
    query->bindValue(":jednostka", unit);
    query->bindValue(":cena", price);
    query->bindValue(":vat", tax);
    query->exec();
    conn.dbClose();

    addProducts::close();
}

void addProducts::on_button_return_clicked()
{
    addProducts::close();
}
