#include "productswindow.h"
#include "ui_productswindow.h"
#include "sql.h"
#include <QtSql>
#include <QtDebug>

productsWindow::productsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::productsWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    sql conn;
    QSqlQueryModel *modal = new QSqlQueryModel;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from produkty");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    conn.dbClose();
}

productsWindow::~productsWindow()
{
    delete ui;
}
