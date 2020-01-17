#include "supplieswindow.h"
#include "ui_supplieswindow.h"
#include <QtDebug>


suppliesWindow::suppliesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::suppliesWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    updateDetails();
}

suppliesWindow::~suppliesWindow()
{
    delete ui;
}

void suppliesWindow::updateDetails(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare(
                   "SELECT faktury.id AS ID, "
                       "kontrahenci.nazwa AS NAZWA, "
                       "faktury.data AS DATA, "
                       "faktury.komentarz AS KOMENTARZ "
                   "FROM faktury,kontrahenci "
                   "WHERE "
                       "faktury.id_kontrahent=kontrahenci.id "
                       "AND kontrahenci.id=1 " //id=1 id dostawy
                   "ORDER BY faktury.data DESC"
                   );
    query->exec();
    QSqlQueryModel *modal = new QSqlQueryModel;
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    conn.dbClose();
    updateComboBox();
}

void suppliesWindow::updateComboBox(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare(
                   "SELECT "
                       "faktury.id AS ID, "
                       "kontrahenci.nazwa AS NAZWA, "
                       "faktury.data AS DATA, "
                       "faktury.komentarz AS KOMENTARZ "
                   "FROM faktury,kontrahenci "
                   "WHERE "
                       "faktury.id_kontrahent=kontrahenci.id "
                       "AND kontrahenci.id=1 " //id=1 id dostawy
                   "ORDER BY faktury.data DESC"
                   );
    query->exec();
    query->seek(-1);
    ui->comboBox->clear();
    ui->comboBox->addItem("");
    while(query->next()){
        ui->comboBox->addItem(query->value(0).toString());
    }
}

void suppliesWindow::on_button_return_clicked()
{
    suppliesWindow::close();
}

void suppliesWindow::on_newSupply_clicked()
{
    salesCreate salesCreate;
    salesCreate.createInvoice("DOSTAWA");
    salesCreate.updateDetails();
    salesCreate.setModal(true);
    salesCreate.exec();
    updateDetails();
}

void suppliesWindow::on_tableView_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    QString value = select->selectedRows(0).value(0).data().toString();

    int comboIndex = ui->comboBox->findText(value);
    if ( comboIndex != -1 ) { // -1 for not found
       ui->comboBox->setCurrentIndex(comboIndex);
    }
}

void suppliesWindow::on_editSupply_clicked()
{
    salesDetail salesDetail;
    salesDetail.updateDetails(ui->comboBox->currentText().toInt());
    salesDetail.setModal(true);
    salesDetail.exec();
    updateDetails();
}
