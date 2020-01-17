#include "editclients.h"
#include "ui_editclients.h"

int editClients::clientId = -1;

editClients::editClients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editClients)
{
    ui->setupUi(this);
    reciveClientId();
}

editClients::~editClients()
{
    delete ui;
}

void editClients::reciveClientId(){
    ui->output_id->setNum(clientId);

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT * FROM kontrahenci WHERE id=:id");
    query->bindValue(":id",clientId);
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
    QString NIP = ui->output_NIP->text();
    QString REGON = ui->output_REGON->text();
    QString KRS = ui->output_KRS->text();
    QString PESEL = ui->output_PESEL->text();
    QString email = ui->output_email->text();
    QString phone = ui->output_phone->text();
    QString city = ui->output_city->text();
    QString street = ui->output_street->text();
    QString number = ui->output_number->text();
    QString postalCode = ui->output_postalCode->text();

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("UPDATE kontrahenci SET "
                   "nazwa=:nazwa, "
                   "NIP=:NIP, "
                   "REGON=:REGON, "
                   "KRS=:KRS, "
                   "PESEL=:PESEL, "
                   "email=:email, "
                   "telefon=:telefon, "
                   "adres_miasto=:adres_miasto, "
                   "adres_ulica=:adres_ulica, "
                   "adres_numer=:adres_numer, "
                   "adres_kodPocztowy=:adres_kodPocztowy "
                   "WHERE id=:id;");

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
    query->bindValue(":id", clientId);

    query->exec();
    conn.dbClose();

    editClients::close();
}

void editClients::on_button_return_clicked()
{
    editClients::close();
}
