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
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from kontrahenci");
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

void clientsWindow::on_button_newClient_clicked()
{
    addClients addClients;
    addClients.setModal(true);
    addClients.exec();
    updateClientsList();
}

void clientsWindow::on_button_editSelected_clicked()
{

}

void clientsWindow::on_button_removeSelected_clicked()
{

}

void clientsWindow::on_button_return_clicked()
{
    clientsWindow::close();
}
