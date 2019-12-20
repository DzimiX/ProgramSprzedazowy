#include "salesappenditem.h"
#include "ui_salesappenditem.h"

salesAppendItem::salesAppendItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesAppendItem)
{
    ui->setupUi(this);
}

salesAppendItem::~salesAppendItem()
{
    delete ui;
}

void salesAppendItem::appendTo(int invoiceId){
    ui->output_invoiceId->setNum(invoiceId);
    fillComboBox();
}

void salesAppendItem::fillComboBox(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from produkty");
    query->exec();
    query->seek(-1);
    while(query->next()){
        ui->comboBox->addItem(query->value(1).toString());
    }
    conn.dbClose();
    refreshStaticText();
}

void salesAppendItem::refreshStaticText(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);
    query->prepare("select id, jednostka, cena, vat from produkty where nazwa=:nazwa");
    query->bindValue(":nazwa",ui->comboBox->currentText());
    query->exec();
    query->seek(0);
    int id = query->value(0).toInt();
    ui->output_unit->setText(query->value(2).toString());
    ui->output_price->setText(query->value(3).toString());
    qDebug() << "id produktu:: " << id;
    int ilosc = productAmount(id);
    QString ilosc_text = QString::number(ilosc);
    ui->output_available->setText(ilosc_text);
    conn.dbClose();
}

void salesAppendItem::on_comboBox_activated()
{
    refreshStaticText();
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
    query->prepare("select * from produkty where nazwa=:nazwa");
    query->bindValue(":nazwa",ui->comboBox->currentText());
    query->exec();
    query->seek(-1);
    query->next();

    int invoiceId = ui->output_invoiceId->text().toInt();
    int productId = query->value(0).toInt();
    int amount = ui->input_amount->text().toInt();
    int amount_max = ui->output_available->text().toInt();

    //pobranie id do rozliczenia - czy dostawa? wtedy warunki nie obowiązują!
    query->prepare("SELECT kontrahenci.id FROM kontrahenci, faktury WHERE faktury.id_kontrahent=kontrahenci.id AND faktury.id=:id_faktura");
    query->bindValue(":id_faktura", invoiceId);
    query->exec();
    query->seek(-1);
    query->next();
    int customerId = query->value(0).toInt();

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
        query->prepare("insert into rozliczenia (id_produkt,id_faktura,ilosc) values (:id_produkt,:id_faktura,:ilosc);");
        query->bindValue(":id_produkt", productId);
        query->bindValue(":id_faktura", invoiceId);
        query->bindValue(":ilosc", amount);
        query->exec();
        salesAppendItem::close();
    }
    conn.dbClose();
}

int salesAppendItem::productAmount(int id){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT id_produkt as ID, Nazwa, sum(ilosc) from "
                   "("
                   "SELECT rozliczenia.id_produkt, produkty.nazwa as Nazwa, sum(rozliczenia.ilosc) as ilosc from produkty,rozliczenia,faktury where rozliczenia.id_produkt=produkty.id and rozliczenia.id_faktura=faktury.id and faktury.id_kontrahent==1 group by rozliczenia.id_produkt "
                   "UNION ALL "
                   "SELECT rozliczenia.id_produkt, produkty.nazwa as Nazwa, sum(-1*rozliczenia.ilosc) as ilosc from produkty,rozliczenia,faktury where rozliczenia.id_produkt=produkty.id and rozliczenia.id_faktura=faktury.id and faktury.id_kontrahent!=1 group by rozliczenia.id_produkt "
                   ") "
                   "WHERE ID=:id "
                   "GROUP BY id_produkt");
    query->bindValue(":id",id);
    query->exec();
    query->seek(0);
    return query->value(2).toInt();
}
