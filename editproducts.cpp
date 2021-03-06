#include "editproducts.h"
#include "ui_editproducts.h"
#include <QDebug>
#include <QObject>
#include "sql.h"
#include <QtSql>
#include "productswindow.h"

editProducts::editProducts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editProducts)
{
    ui->setupUi(this);
}

editProducts::~editProducts()
{
    delete ui;
}

void editProducts::reciveProductId(int id){
    ui->output_id->setNum(id);

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT * FROM produkty WHERE id=:id");
    query->bindValue(":id",id);
    query->exec();

    query->seek(-1);
    while(query->next()){
        ui->input_name->setText(query->value(1).toString());
        ui->input_unit->setText(query->value(2).toString());
        ui->input_price->setText(query->value(3).toString());
        ui->input_tax->setText(query->value(4).toString());
    }

    conn.dbClose();
}

void editProducts::on_pushButton_clicked()
{
    QString name = ui->input_name->text();
    QString unit = ui->input_unit->text();
    double price = ui->input_price->text().toDouble();
    int tax = ui->input_tax->text().toInt();
    int id = ui->output_id->text().toInt();

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("UPDATE produkty "
                   "SET "
                       "nazwa=:nazwa, "
                       "jednostka=:jednostka, "
                       "cena=:cena, "
                       "VAT=:vat "
                   "WHERE id=:id;");

    query->bindValue(":nazwa", name);
    query->bindValue(":jednostka", unit);
    query->bindValue(":cena", price);
    query->bindValue(":vat", tax);
    query->bindValue(":id", id);
    query->exec();
    conn.dbClose();

    editProducts::close();
}

void editProducts::on_pushButton_2_clicked()
{
    editProducts::close();
}
