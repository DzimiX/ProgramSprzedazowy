#include "salesappenditem.h"
#include "ui_salesappenditem.h"

int salesAppendItem::invoiceId = -1;
int salesAppendItem::customerId = -1;

salesAppendItem::salesAppendItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesAppendItem)
{
    ui->setupUi(this);
    ui->output_invoiceId->setNum(invoiceId);
    fillComboBox();

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT kontrahenci.id FROM "
                   "kontrahenci, faktury "
                   "WHERE "
                   "faktury.id_kontrahent=kontrahenci.id "
                   "AND "
                   "faktury.id=:id_faktura");
    query->bindValue(":id_faktura", invoiceId);
    query->exec();
    query->seek(-1);
    query->next();
    customerId = query->value(0).toInt();

    if(customerId==1){
        ui->label_7->hide();
        ui->label_8->hide();
        ui->output_unit->hide();
        ui->output_price->hide();
    }
}

salesAppendItem::~salesAppendItem()
{
    delete ui;
}

void salesAppendItem::fillComboBox(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT * FROM produkty");
    query->exec();
    query->seek(-1);
    while(query->next()){
        ui->comboBox->addItem(query->value(1).toString());
    }
    conn.dbClose();
    updateDetails();
}

void salesAppendItem::updateDetails(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("SELECT "
                   "id, "
                   "jednostka, "
                   "cena, "
                   "vat "
                   "FROM "
                   "produkty "
                   "WHERE nazwa=:nazwa");
    query->bindValue(":nazwa",ui->comboBox->currentText());
    query->exec();
    query->seek(0);
    int productId = query->value(0).toInt();
    ui->output_unit->setText(query->value(2).toString());
    ui->output_price->setText(query->value(3).toString());
    int ilosc = productAmount(productId);
    QString ilosc_text = QString::number(ilosc);
    ui->output_available->setText(ilosc_text);
    conn.dbClose();
}

void salesAppendItem::on_comboBox_activated()
{
    updateDetails();
}

void salesAppendItem::on_button_return_clicked()
{
    salesAppendItem::close();
}

void salesAppendItem::on_button_add_clicked()
{
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("SELECT * FROM produkty WHERE nazwa=:nazwa");
    query->bindValue(":nazwa",ui->comboBox->currentText());
    query->exec();
    query->seek(-1);
    query->next();

    int productId = query->value(0).toInt();
    int amount = ui->input_amount->text().toInt();
    int amount_max = ui->output_available->text().toInt();

    if(amount <= 0 && customerId != 1 ){ //gdy customerId = 1 to dostawa i nie ma znaczeina ile mamy produktu!
        QMessageBox::critical(this,
                             "Błąd!",
                             "Niepoprawna wartość!",
                             QMessageBox::Ok);
    }else if (amount > amount_max && customerId != 1 ){
        QMessageBox::warning(this,
                             "Ostrzeżenie!",
                             "Nie posiadasz takiej ilości towaru w magazynie!",
                             QMessageBox::Ok);
    }else {
        query->prepare("INSERT INTO rozliczenia "
                       "(id_produkt,id_faktura,ilosc) "
                       "VALUES "
                       "(:id_produkt,:id_faktura,:ilosc);");
        query->bindValue(":id_produkt", productId);
        query->bindValue(":id_faktura", invoiceId);
        query->bindValue(":ilosc", amount);
        query->exec();
        salesAppendItem::close();
    }
    conn.dbClose();
}

int salesAppendItem::productAmount(int productId){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT id_produkt as ID, Nazwa, sum(ilosc) FROM "
                   "("
                       "SELECT "
                           "rozliczenia.id_produkt, "
                           "produkty.nazwa AS Nazwa, "
                           "sum(rozliczenia.ilosc) as ilosc "
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
                   "WHERE ID=:id "
                   "GROUP BY id_produkt");
    query->bindValue(":id",productId);
    query->exec();
    query->seek(0);
    return query->value(2).toInt();
}
