#include "companywindow.h"
#include "ui_companywindow.h"

companyWindow::companyWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::companyWindow)
{
    ui->setupUi(this);

    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from firma;");
    query->exec();

    query->seek(-1); //ustawienie indeksu przed pierwszy element
    query->next(); //przejście na 1 element (istnieje tylko 1)

    ui->output_name->setText(query->value(0).toString());
    ui->output_NIP->setText(query->value(1).toString());
    ui->output_REGON->setText(query->value(2).toString());
    ui->output_KRS->setText(query->value(3).toString());
    ui->output_PESEL->setText(query->value(4).toString());
    ui->output_email->setText(query->value(5).toString());
    ui->output_phone->setText(query->value(6).toString());
    ui->output_city->setText(query->value(7).toString());
    ui->output_street->setText(query->value(8).toString());
    ui->output_number->setText(query->value(9).toString());
    ui->output_postalCode->setText(query->value(10).toString());

    conn.dbClose();
}

companyWindow::~companyWindow()
{
    delete ui;
}

void companyWindow::on_pushButton_2_clicked()
{
    QString name = ui->output_name->text();
    int NIP = ui->output_NIP->text().toInt();
    int REGON = ui->output_REGON->text().toInt();
    int KRS = ui->output_KRS->text().toInt();
    int PESEL = ui->output_PESEL->text().toInt();
    QString email = ui->output_email->text();
    QString telefon = ui->output_phone->text();
    QString adres_miasto = ui->output_city->text();
    QString adres_ulica = ui->output_street->text();
    QString adres_numer = ui->output_number->text();
    QString adres_kodPocztowy = ui->output_postalCode->text();

    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("UPDATE firma SET nazwa=:nazwa,NIP=:NIP,REGON=:REGON,KRS=:KRS,PESEL=:PESEL,email=:email,telefon=:telefon,adres_miasto=:adres_miasto,adres_ulica=:adres_ulica,adres_numer=:adres_numer,adres_kodPocztowy=:adres_kodPocztowy WHERE 1=1;");
    query->bindValue(":nazwa", name);
    query->bindValue(":NIP", NIP);
    query->bindValue(":REGON", REGON);
    query->bindValue(":KRS", KRS);
    query->bindValue(":PESEL", PESEL);
    query->bindValue(":email", email);
    query->bindValue(":telefon", telefon);
    query->bindValue(":adres_miasto", adres_miasto);
    query->bindValue(":adres_ulica", adres_ulica);
    query->bindValue(":adres_numer", adres_numer);
    query->bindValue(":adres_kodPocztowy", adres_kodPocztowy);
    query->exec();
    conn.dbClose();

    companyWindow::close();
}

void companyWindow::on_pushButton_clicked()
{
    companyWindow::close();
}
