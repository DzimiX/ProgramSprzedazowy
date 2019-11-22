#include "addclients.h"
#include "ui_addclients.h"

addClients::addClients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addClients)
{
    ui->setupUi(this);
}

addClients::~addClients()
{
    delete ui;
}

void addClients::on_button_add_clicked()
{
    QString name = ui->output_name->text();
    int NIP = ui->output_NIP->text().toInt();
    int REGON = ui->output_REGON->text().toInt();
    int KRS = ui->output_KRS->text().toInt();
    int PESEL = ui->output_PESEL->text().toInt();
    QString email = ui->output_email->text();
    QString phone = ui->output_phone->text();
    QString city = ui->output_city->text();
    QString street = ui->output_street->text();
    QString number = ui->output_number->text();
    QString postalCode = ui->output_postalCode->text();

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("insert into kontrahenci (nazwa, NIP, REGON, KRS, PESEL, email, telefon, adres_miasto, adres_ulica, adres_numer, adres_kodPocztowy) values (:nazwa, :NIP, :REGON, :KRS, :PESEL, :email, :telefon, :adres_miasto, :adres_ulica, :adres_numer, :adres_kodPocztowy)");
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
    query->exec();
    conn.dbClose();

    addClients::close();
}

void addClients::on_button_return_clicked()
{
    addClients::close();
}
