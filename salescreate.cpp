#include "salescreate.h"
#include "ui_salescreate.h"


salesCreate::salesCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesCreate)
{
    ui->setupUi(this);
}

salesCreate::~salesCreate()
{
    delete ui;
}

void salesCreate::on_button_quit_clicked()
{
    salesCreate::close();
}

void salesCreate::createInvoice(QString clientName){
    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from kontrahenci where nazwa=:nazwa"); //nazwa jest unikalna dla każdego kontrahenta
    query->bindValue(":nazwa",clientName);
    query->exec();

    query->seek(-1);
    query->next();
    int clientID = query->value(0).toInt();
    qDebug() << "id klienta: " << clientID;
    qDebug() << "data: " << QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" );

    query->prepare("insert into faktury (id_kontrahent, data) values (:id_kontrahent, :data);");
    query->bindValue(":id_kontrahent",clientID);
    query->bindValue(":data",QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" ));
    query->exec();

    query->prepare("SELECT last_insert_rowid();");
    query->exec();
    query->seek(-1);
    query->next();
    ui->output_id->setText(query->value(0).toString());

    conn.dbClose();
    salesCreate::updateDetails();
}

void salesCreate::updateDetails(){
    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    int id = ui->output_id->text().toInt();

    query->prepare("select * from faktury where id=:id");
    query->bindValue(":id",id);
    query->exec();
    query->seek(-1);
    query->next();
    int clientId = query->value(1).toInt();
    QString type = query->value(2).toString();
    QString comment = query->value(3).toString();
    QString date = query->value(4).toString();

    query->prepare("select * from kontrahenci where id=:id"); //nazwa jest unikalna dla każdego kontrahenta
    query->bindValue(":id",clientId);
    query->exec();
    query->seek(-1);
    query->next();
    QString clientName = query->value(1).toString();

    id=11;
    //nie dziala?
    //jednak działa
    //przerobić query żeby wyświetlało nazwę produktu i ilość
    query->prepare("select produkty.nazwa,rozliczenia.ilosc from rozliczenia,produkty where rozliczenia.id_faktura=:id_faktura and rozliczenia.id_produkt=produkty.id");
    query->bindValue(":id_faktura",id);
    query->exec();
    QSqlQueryModel *modal = new QSqlQueryModel;
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    query->seek(-1);
    while(query->next()){
        qDebug() << query->value(0);
    }
    conn.dbClose();

    ui->output_date->setText(date);
    ui->output_client->setText(clientName);
}

void salesCreate::on_pushButton_clicked()
{
    salesCreate::updateDetails();
}
