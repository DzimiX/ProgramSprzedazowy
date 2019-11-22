#include "productswindow.h"
#include "ui_productswindow.h"

productsWindow::productsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::productsWindow)
{   
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    updateProductList();
}

productsWindow::~productsWindow()
{
    delete ui;
}

void productsWindow::updateProductList(){
    sql conn;
    QSqlQueryModel *modal = new QSqlQueryModel;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from produkty");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    ui->combo_select->clear();
    ui->combo_select->addItem("ID");

    query->seek(-1); //ustawienie indeksu przed pierwszy element
    while(query->next()){ //przeskok na 1 element (za 1 razem)
        //qDebug() << query->value(0).toInt();
        ui->combo_select->addItem(query->value(0).toString());
    }

    conn.dbClose();
}

void productsWindow::on_button_addNew_clicked()
{
    QString name = ui->input_name->text();
    QString unit = ui->input_unit->text();
    double price = ui->input_price->text().toDouble();
    int tax = ui->input_tax->text().toInt();

    //qDebug() << "Name: " << name << " Unit: " << unit << " Price: " << price << " Tax: " << tax; //ok

    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("insert into produkty (nazwa, jednostka, cena, vat) VALUES (:nazwa, :jednostka, :cena, :vat);");
    query->bindValue(":nazwa", name);
    query->bindValue(":jednostka", unit);
    query->bindValue(":cena", price);
    query->bindValue(":vat", tax);
    query->exec();
    //qDebug() << query;
    conn.dbClose();

    updateProductList();
}

void productsWindow::on_button_editSelected_clicked()
{
    if(ui->combo_select->currentText()=="ID"){
        qDebug() << "Nie wybrano rekordu!";
    }else{
        int id = ui->combo_select->currentText().toInt();
        //qDebug() << id;

        //updateProductList();

        editProducts editProducts;
        editProducts.setModal(true);
        editProducts.reciveProductId(id);
        editProducts.exec();
        updateProductList();
    }
}

void productsWindow::on_button_removeSelected_clicked()
{
    if(ui->combo_select->currentText()=="ID"){
        qDebug() << "Nie wybrano rekordu!";
    }else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Usuwanie rekordu", "Czy napewno chcesz usunąć ten rekord?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            int id = ui->combo_select->currentText().toInt();
            sql conn;
            conn.dbOpen(conn.location);
            QSqlQuery *query = new QSqlQuery(conn.db);
            query->prepare("delete from produkty where id=:id");
            query->bindValue(":id",id);
            query->exec();
            conn.dbClose();
            updateProductList();
        } else {
            updateProductList();
        }
    }
}

void productsWindow::on_tableView_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    QString value = select->selectedRows(0).value(0).data().toString();

    int comboIndex = ui->combo_select->findText(value);
    if ( comboIndex != -1 ) { // -1 for not found
       ui->combo_select->setCurrentIndex(comboIndex);
    }
}

void productsWindow::on_button_return_clicked()
{
    productsWindow::close();
}

void productsWindow::on_button_newProduct_clicked()
{
    addProducts addProducts;
    addProducts.setModal(true);
    addProducts.exec();
    updateProductList();
}
