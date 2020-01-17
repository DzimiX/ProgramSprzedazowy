#include "clientswindow.h"
#include "ui_clientswindow.h"

clientsWindow::clientsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clientsWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    updateClientsList();
}

clientsWindow::~clientsWindow()
{
    delete ui;
}

void clientsWindow::updateClientsList(){
    sql conn;
    QSqlQueryModel *modal = new QSqlQueryModel;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT * FROM kontrahenci");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    ui->combo_select->clear();
    ui->combo_select->addItem("ID");

    query->seek(-1); //ustawienie indeksu przed pierwszy element
    while(query->next()){ //przeskok na 1 element (za 1 razem)
        ui->combo_select->addItem(query->value(0).toString());
    }

    conn.dbClose();
}

void clientsWindow::on_button_newClient_clicked()
{
    addClients addClients;
    addClients.setModal(true);
    addClients.exec();
    updateClientsList();
}

void clientsWindow::on_button_editSelected_clicked()
{
    if(ui->combo_select->currentText()=="ID" || ui->combo_select->currentText()=="1" || ui->combo_select->currentText()=="2"){
        qDebug() << "Wybrano niepoprawny rekord!";
    }else{
        int id = ui->combo_select->currentText().toInt();

        editClients::clientId = id;
        editClients editClients;
        editClients.setModal(true);
        editClients.exec();
        updateClientsList();
    }
}

void clientsWindow::on_button_removeSelected_clicked()
{
    if(ui->combo_select->currentText()=="ID" || ui->combo_select->currentText()=="1" || ui->combo_select->currentText()=="2"){
        qDebug() << "Wybrano niepoprawny rekord!";
    }else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Usuwanie rekordu", "Czy napewno chcesz usunąć ten rekord?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            int id = ui->combo_select->currentText().toInt();
            sql conn;
            conn.dbOpen(conn.location);
            QSqlQuery *query = new QSqlQuery(conn.db);
            query->prepare("DELETE FROM kontrahenci WHERE id=:id");
            query->bindValue(":id",id);
            query->exec();
            conn.dbClose();
            updateClientsList();
        } else {
            updateClientsList();
        }
    }
}

void clientsWindow::on_button_return_clicked()
{
    clientsWindow::close();
}

void clientsWindow::on_tableView_clicked()
{
    QItemSelectionModel *select = ui->tableView->selectionModel();
    QString value = select->selectedRows(0).value(0).data().toString();

    int comboIndex = ui->combo_select->findText(value);
    if ( comboIndex != -1 ) { // -1 for not found
       ui->combo_select->setCurrentIndex(comboIndex);
    }
}
