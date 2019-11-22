#include "storagewindow.h"
#include "ui_storagewindow.h"

storageWindow::storageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::storageWindow)
{
    ui->setupUi(this);
}

storageWindow::~storageWindow()
{
    delete ui;
}

void storageWindow::on_button_return_clicked()
{
    storageWindow::close();
}

void storageWindow::updateDetails(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select produkty.id,sum(rozliczenia.ilosc) from produkty,rozliczenia,faktury,kontrahenci where produkty.id=rozliczenia.id_produkt and faktury.id=rozliczenia.id_faktura and kontrahenci.id=faktury.id_kontrahent and id_kontrahent=1 group by produkty.id;");
    query->exec();

    //QSqlQueryModel *modal = new QSqlQueryModel;
    //modal->setQuery(*query);
    //ui->tableView->setModel(modal);

    conn.dbClose();
}
