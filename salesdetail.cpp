#include "salesdetail.h"
#include "ui_salesdetail.h"

salesDetail::salesDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesDetail)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

salesDetail::~salesDetail()
{
    delete ui;
}

void salesDetail::updateDetails(int invoiceId){
    ui->output_invoiceId->setNum(invoiceId);
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("select kontrahenci.nazwa,faktury.data from faktury,kontrahenci where faktury.id=:id and faktury.id_kontrahent=kontrahenci.id");
    query->bindValue(":id",invoiceId);
    query->exec();
    query->seek(-1);
    query->next();
    ui->output_clientName->setText(query->value(0).toString());
    ui->output_date->setText(query->value(1).toString());

    query->prepare("select rozliczenia.id, produkty.nazwa as Nazwa,produkty.cena as Cena, produkty.VAT as VAT,rozliczenia.ilosc as Ilość, (produkty.cena * rozliczenia.ilosc) as Netto, (produkty.cena * produkty.VAT * 0.01 * rozliczenia.ilosc) as 'Suma VAT', (produkty.cena * rozliczenia.ilosc + produkty.cena * produkty.VAT * 0.01 * rozliczenia.ilosc) as Brutto from rozliczenia,produkty where rozliczenia.id_faktura=:id_faktura and rozliczenia.id_produkt=produkty.id");
    query->bindValue(":id_faktura",invoiceId);
    query->exec();
    QSqlQueryModel *modal = new QSqlQueryModel;
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    conn.dbClose();

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
}

void salesDetail::on_button_return_clicked()
{
    salesDetail::close();
}

void salesDetail::on_button_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Anulowanie zamówienia", "Czy napewno chcesz anulować zamówienie? (tej operacji nie można cofnąć)", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        sql conn;
        conn.dbOpen(conn.location);
        QSqlQuery *query = new QSqlQuery(conn.db);
        int id = ui->output_invoiceId->text().toInt();
        query->prepare("delete from rozliczenia where id_faktura=:id_faktura");
        query->bindValue(":id_faktura",id);
        query->exec();
        query->prepare("delete from faktury where id=:id");
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
    pdf.printInvoice(id);
}
