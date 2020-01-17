#include "salescreate.h"
#include "ui_salescreate.h"

int salesCreate::invoiceId = -1;

salesCreate::salesCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesCreate)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT * FROM kontrahenci WHERE nazwa=:nazwa"); //nazwa jest unikalna dla każdego kontrahenta
    query->bindValue(":nazwa",clientName);
    query->exec();

    query->seek(-1);
    query->next();
    int clientID = query->value(0).toInt();

    if(clientID==1){
        ui->label_2->setText("Dostawa nr: ");
        ui->label->setText("<b>Aktualnie w dostawie:<b> ");
        ui->label->setAlignment(Qt::AlignRight);
        ui->label_2->setAlignment(Qt::AlignRight);
        ui->label_3->hide();
        ui->label_6->hide();
        ui->label_7->hide();
        ui->label_11->hide();
        ui->output_net->hide();
        ui->output_tax->hide();
        ui->output_gross->hide();
        ui->output_client->hide();
    }

    query->prepare("INSERT INTO faktury (id_kontrahent, data) VALUES (:id_kontrahent, :data);");
    query->bindValue(":id_kontrahent",clientID);
    query->bindValue(":data",QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" ));
    query->exec();

    query->prepare("SELECT last_insert_rowid();");
    query->exec();
    query->seek(-1);
    query->next();
    invoiceId = query->value(0).toInt();
    ui->output_id->setText(QString::number(invoiceId));

    conn.dbClose();
    salesCreate::updateDetails();
}

void salesCreate::updateDetails(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    int id = ui->output_id->text().toInt();

    query->prepare("SELECT * FROM faktury WHERE id=:id");
    query->bindValue(":id",id);
    query->exec();
    query->seek(-1);
    query->next();
    int clientId = query->value(1).toInt();
    QString type = query->value(2).toString();
    QString comment = query->value(3).toString();
    QString date = query->value(4).toString();

    query->prepare("SELECT * FROM kontrahenci WHERE id=:id"); //nazwa jest unikalna dla każdego kontrahenta
    query->bindValue(":id",clientId);
    query->exec();
    query->seek(-1);
    query->next();
    QString clientName = query->value(1).toString();

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
    query->bindValue(":id_faktura",id);
    query->exec();
    QSqlQueryModel *modal = new QSqlQueryModel;
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    conn.dbClose();

    ui->output_date->setText(date);
    ui->output_client->setText(clientName);

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

    fillCombo();
}

void salesCreate::on_button_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Anulowanie zamówienia",
                                  "Czy napewno chcesz anulować zamówienie? (tej operacji nie można cofnąć)",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        sql conn;
        conn.dbOpen(conn.location);
        QSqlQuery *query = new QSqlQuery(conn.db);
        int id = ui->output_id->text().toInt();
        query->prepare("DELETE FROM rozliczenia WHERE id_faktura=:id_faktura");
        query->bindValue(":id_faktura",id);
        query->exec();
        query->prepare("DELETE FROM faktury WHERE id=:id");
        query->bindValue(":id",id);
        query->exec();
        conn.dbClose();
        salesCreate::close();
    } else {
        updateDetails();
    }
}

void salesCreate::on_button_addElement_clicked()
{
    salesAppendItem::invoiceId = invoiceId;
    qDebug() << invoiceId;
    salesAppendItem salesAppendItem;
    salesAppendItem.setModal(true);
    salesAppendItem.exec();
    updateDetails();
}

void salesCreate::fillCombo(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("SELECT id FROM rozliczenia WHERE id_faktura=:id_faktura"); //nazwa jest unikalna dla każdego kontrahenta
    int id = ui->output_id->text().toInt();
    query->bindValue(":id_faktura",id);
    query->exec();
    query->seek(-1);
    ui->comboBox->clear();
    ui->comboBox->addItem("");
    while(query->next()){
        ui->comboBox->addItem( query->value(0).toString() );
    }
}

void salesCreate::on_tableView_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    QString value = select->selectedRows(0).value(0).data().toString();

    int comboIndex = ui->comboBox->findText(value);
    if ( comboIndex != -1 ) { // -1 for not found
       ui->comboBox->setCurrentIndex(comboIndex);
    }
}

void salesCreate::on_button_removeElement_clicked()
{
    int id = ui->comboBox->currentText().toInt();
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("DELETE FROM rozliczenia WHERE id=:id");
    query->bindValue(":id",id);
    query->exec();
    updateDetails();
}

void salesCreate::on_button_print_clicked()
{
    int id = ui->output_id->text().toInt();
    sql pdf;
    pdf.dbCreatePdf(id);
}
