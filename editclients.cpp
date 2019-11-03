#include "editclients.h"
#include "ui_editclients.h"

editClients::editClients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editClients)
{
    ui->setupUi(this);
}

editClients::~editClients()
{
    delete ui;
}

void editClients::reciveClientId(int id){
    ui->output_id->setNum(id);

    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from kontrahenci where id=:id");
    query->bindValue(":id",id);
    query->exec();

    query->seek(-1);
    while(query->next()){
        ui->output_name->setText(query->value(1).toString());
        ui->output_NIP->setText(query->value(2).toString());
        ui->output_REGON->setText(query->value(3).toString());
        ui->output_KRS->setText(query->value(4).toString());
        ui->output_PESEL->setText(query->value(5).toString());
        ui->output_email->setText(query->value(6).toString());
        ui->output_phone->setText(query->value(7).toString());
        ui->output_city->setText(query->value(8).toString());
        ui->output_street->setText(query->value(9).toString());
        ui->output_number->setText(query->value(10).toString());
        ui->output_postalCode->setText(query->value(11).toString());
    }
    conn.dbClose();
}

void editClients::on_button_update_clicked()
{
    QString name = ui->output_name->text();
    QVariant NIP = ui->output_NIP->text();
    QVariant REGON = ui->output_REGON->text();
    QVariant KRS = ui->output_KRS->text();
    QVariant PESEL = ui->output_PESEL->text();
    QString email = ui->output_email->text();
    QString phone = ui->output_phone->text();
    QString city = ui->output_city->text();
    QString street = ui->output_street->text();
    QString number = ui->output_number->text();
    QString postalCode = ui->output_postalCode->text();
    int id = ui->output_id->text().toInt();

    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("update kontrahenci set nazwa=:nazwa,NIP=:NIP,REGON=:REGON,KRS=:KRS,PESEL=:PESEL,email=:email,telefon=:telefon,adres_miasto=:adres_miasto,adres_ulica=:adres_ulica,adres_numer=:adres_numer,adres_kodPocztowy=:adres_kodPocztowy where id=:id;");
    //qDebug() << query;
    query->bindValue(":nazwa", name);
    query->bindValue(":NIP", NIP);
    query->bindValue(":REGON", REGON);
    query->bindValue(":KRS", KRS);
    query->bindValue(":PESEL", PESEL);
    query->bindValue(":email", email);
    query->bindValue(":telefon", phone);
    query->bindValue(":adres_miasto", city);
    query->bindValue(":adres_ulica", street);
    query->bindValue(":adres_numer", number);
    query->bindValue(":adres_kodPocztowy", postalCode);
    query->bindValue(":id", id);

    query->exec();
    conn.dbClose();

    editClients::close();
}

void editClients::on_button_return_clicked()
{
    editClients::close();
}
