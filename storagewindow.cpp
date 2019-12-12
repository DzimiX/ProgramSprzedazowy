#include "storagewindow.h"
#include "ui_storagewindow.h"

storageWindow::storageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::storageWindow)
{
    ui->setupUi(this);
    updateDetails();
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

    query->prepare("SELECT id_produkt as ID, Nazwa, sum(ilosc) from "
                   "("
                   "SELECT rozliczenia.id_produkt, produkty.nazwa as Nazwa, rozliczenia.ilosc as ilosc from produkty,rozliczenia,faktury where rozliczenia.id_produkt=produkty.id and rozliczenia.id_faktura=faktury.id and faktury.id_kontrahent==1 group by rozliczenia.id_produkt "
                   "UNION ALL "
                   "SELECT rozliczenia.id_produkt, produkty.nazwa as Nazwa, -1*rozliczenia.ilosc as ilosc from produkty,rozliczenia,faktury where rozliczenia.id_produkt=produkty.id and rozliczenia.id_faktura=faktury.id and faktury.id_kontrahent!=1 group by rozliczenia.id_produkt "
                   ") "
                   "GROUP BY id_produkt");
    query->exec();

    QSqlQueryModel *modal = new QSqlQueryModel;
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    conn.dbClose();
}
