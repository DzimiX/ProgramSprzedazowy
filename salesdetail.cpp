#include "salesdetail.h"
#include "ui_salesdetail.h"

int salesDetail::invoiceId = -1;

salesDetail::salesDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesDetail)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    updateDetails();
}

salesDetail::~salesDetail()
{
    delete ui;
}

void salesDetail::updateDetails(){
    ui->output_invoiceId->setNum(invoiceId);
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("SELECT "
                       "kontrahenci.id, "
                       "kontrahenci.nazwa, "
                       "faktury.data "
                   "FROM faktury,kontrahenci "
                   "WHERE "
                       "faktury.id=:id "
                       "AND faktury.id_kontrahent=kontrahenci.id");
    query->bindValue(":id",invoiceId);
    query->exec();
    query->seek(-1);
    query->next();
    int clientId = query->value(0).toInt();
    ui->output_clientName->setText(query->value(1).toString());
    ui->output_date->setText(query->value(2).toString());

    query->prepare("SELECT "
                       "rozliczenia.id, "
                       "produkty.nazwa AS Nazwa, "
                       "produkty.cena AS Cena, "
                       "produkty.VAT AS VAT, "
                       "rozliczenia.ilosc AS Ilość, "
                       "(produkty.cena * rozliczenia.ilosc) AS Netto, "
                       "(produkty.cena * produkty.VAT * 0.01 * rozliczenia.ilosc) AS 'Suma VAT', "
                       "(produkty.cena * rozliczenia.ilosc + produkty.cena * produkty.VAT * 0.01 * rozliczenia.ilosc) AS Brutto "
                   "FROM rozliczenia,produkty "
                   "WHERE "
                       "rozliczenia.id_faktura=:id_faktura "
                       "AND rozliczenia.id_produkt=produkty.id");
    query->bindValue(":id_faktura",invoiceId);
    query->exec();
    QSqlQueryModel *modal = new QSqlQueryModel;
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    conn.dbClose();

    if(clientId!=1){
        double net = 0;
        double gross = 0;
        double tax = 0;

        for (int row = 0; row < ui->tableView->model()->rowCount(); ++row) {
            net += ui->tableView->model()->data(ui->tableView->model()->index(row,5)).toDouble();
            tax += ui->tableView->model()->data(ui->tableView->model()->index(row,6)).toDouble();
            gross += ui->tableView->model()->data(ui->tableView->model()->index(row,7)).toDouble();
        }
        ui->output_net->setNum(net);
        ui->output_gross->setNum(gross);
        ui->output_tax->setNum(tax);
    } else {
        ui->output_net->hide();
        ui->output_tax->hide();
        ui->output_gross->hide();
        ui->label_3->hide();
        ui->label_5->hide();
        ui->label_6->hide();
        ui->label_7->hide();
        ui->label->setText("Szczegóły dostawy o nr:");
    }
}

void salesDetail::on_button_return_clicked()
{
    salesDetail::close();
}

void salesDetail::on_button_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Anulowanie zamówienia",
                                  "Czy napewno chcesz anulować zamówienie? (tej operacji nie można cofnąć)",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        sql conn;
        conn.dbOpen(conn.location);
        QSqlQuery *query = new QSqlQuery(conn.db);
        int id = ui->output_invoiceId->text().toInt();
        query->prepare("DELETE FROM rozliczenia WHERE id_faktura=:id_faktura");
        query->bindValue(":id_faktura",id);
        query->exec();
        query->prepare("DELETE FROM faktury WHERE id=:id");
        query->bindValue(":id",id);
        query->exec();
        conn.dbClose();
        salesDetail::close();
    }
}

void salesDetail::on_button_print_clicked()
{
    int id = ui->output_invoiceId->text().toInt();
    sql pdf;
    pdf.dbCreatePdf(id);
}
