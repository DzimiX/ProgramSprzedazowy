#include "storagewindow.h"
#include "ui_storagewindow.h"

storageWindow::storageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::storageWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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

    query->prepare("SELECT id_produkt AS ID, Nazwa, sum(ilosc) AS 'Suma produktów' FROM "
                   "("
                       "SELECT "
                           "rozliczenia.id_produkt, "
                           "produkty.nazwa AS Nazwa, "
                           "sum(rozliczenia.ilosc) AS ilosc "
                       "FROM produkty,rozliczenia,faktury "
                       "WHERE "
                           "rozliczenia.id_produkt=produkty.id "
                           "AND rozliczenia.id_faktura=faktury.id "
                           "AND faktury.id_kontrahent==1 "
                       "GROUP BY rozliczenia.id_produkt "

                       "UNION ALL "

                       "SELECT "
                           "rozliczenia.id_produkt, "
                           "produkty.nazwa AS Nazwa, "
                           "sum(-1*rozliczenia.ilosc) AS ilosc "
                       "FROM produkty,rozliczenia,faktury "
                       "WHERE "
                           "rozliczenia.id_produkt=produkty.id "
                           "AND rozliczenia.id_faktura=faktury.id "
                           "AND faktury.id_kontrahent!=1 "
                       "GROUP BY rozliczenia.id_produkt "
                   ") "
                   "GROUP BY id_produkt");
    query->exec();

    QSqlQueryModel *modal = new QSqlQueryModel;
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    conn.dbClose();
}
