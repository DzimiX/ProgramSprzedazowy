#include "salesappenditem.h"
#include "ui_salesappenditem.h"

salesAppendItem::salesAppendItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesAppendItem)
{
    ui->setupUi(this);
}

salesAppendItem::~salesAppendItem()
{
    delete ui;
}

void salesAppendItem::appendTo(int invoiceId){
    ui->output_invoiceId->setNum(invoiceId);
    fillComboBox();
}

void salesAppendItem::fillComboBox(){
    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from produkty");
    query->exec();
    query->seek(-1);
    while(query->next()){
        ui->comboBox->addItem(query->value(1).toString());
    }
    conn.dbClose();
    refreshStaticText();
}

void salesAppendItem::refreshStaticText(){
    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("select * from produkty where nazwa=:nazwa");
    query->bindValue(":nazwa",ui->comboBox->currentText());
    query->exec();
    query->seek(-1);
    query->next();
    ui->output_unit->setText(query->value(2).toString());
    ui->output_price->setText(query->value(3).toString());
    conn.dbClose();
}

void salesAppendItem::on_comboBox_activated()
{
    refreshStaticText();
}

void salesAppendItem::on_button_return_clicked()
{
    salesAppendItem::close();
}

void salesAppendItem::on_button_add_clicked()
{
    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("select * from produkty where nazwa=:nazwa");
    query->bindValue(":nazwa",ui->comboBox->currentText());
    query->exec();
    query->seek(-1);
    query->next();

    int invoiceId = ui->output_invoiceId->text().toInt();
    int productId = query->value(0).toInt();
    int amount = ui->input_amount->text().toInt();
    //int amount_max - miejsce na sprawdzenie ile jest w magazynie

    if(amount <= 0 ){
        qDebug() << "Niepoprawna liczba!";
    }else{
        query->prepare("insert into rozliczenia (id_produkt,id_faktura,ilosc) values (:id_produkt,:id_faktura,:ilosc);");
        query->bindValue(":id_produkt", productId);
        query->bindValue(":id_faktura", invoiceId);
        query->bindValue(":ilosc", amount);
        query->exec();
        salesAppendItem::close();
    }
    conn.dbClose();
}
