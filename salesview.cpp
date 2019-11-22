#include "salesview.h"
#include "ui_salesview.h"

salesView::salesView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesView)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    updateDisplay();
}

salesView::~salesView()
{
    delete ui;
}

void salesView::on_button_return_clicked()
{
    salesView::close();
}

void salesView::updateDisplay(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select faktury.id as ID,kontrahenci.nazwa as Kontrahent,faktury.data as Data,faktury.komentarz as Komentarz from faktury,kontrahenci where faktury.id_kontrahent=kontrahenci.id order by faktury.data desc;");
    query->exec();
    QSqlQueryModel *modal = new QSqlQueryModel;
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    conn.dbClose();

    updateComboBox();
}

void salesView::updateComboBox(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select faktury.id from faktury,kontrahenci where faktury.id_kontrahent=kontrahenci.id order by faktury.id;");
    query->exec();
    query->seek(-1);
    ui->comboBox->clear();
    ui->comboBox->addItem("");
    while(query->next()){
        ui->comboBox->addItem(query->value(0).toString());
    }
}

void salesView::on_tableView_clicked(const QModelIndex &index)
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    QString value = select->selectedRows(0).value(0).data().toString();

    int comboIndex = ui->comboBox->findText(value);
    if ( comboIndex != -1 ) { // -1 for not found
       ui->comboBox->setCurrentIndex(comboIndex);
    }
}


void salesView::on_button_details_clicked()
{
    salesDetail salesDetail;
    salesDetail.updateDetails(ui->comboBox->currentText().toInt());
    salesDetail.setModal(true);
    salesDetail.exec();
    updateDisplay();
}
