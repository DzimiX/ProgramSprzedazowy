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

    query->prepare("INSERT INTO produkty "
                   "(nazwa, jednostka, cena, vat) "
                   "VALUES "
                   "(:nazwa, :jednostka, :cena, :vat)");

    query->bindValue(":nazwa", name);
    query->bindValue(":jednostka", unit);
    query->bindValue(":cena", price);
    query->bindValue(":vat", tax);
    query->exec();

    //return last id
    query->prepare("SELECT id FROM produkty ORDER BY id DESC LIMIT 1");
    query->exec();
    query->seek(0);
    int id_produkt = query->value(0).toInt();

    //add init delivery with amount of 0 to make storage amount work properly
    query->prepare("INSERT INTO rozliczenia "
                   "( id_produkt, id_faktura, ilosc ) "
                   "VALUES "
                   "( :id_produkt, 1, 0 )");
    query->bindValue(":id_produkt", id_produkt);
    query->exec();
    conn.dbClose();

    addProducts::close();
}

void addProducts::on_button_return_clicked()
{
    addProducts::close();
}
