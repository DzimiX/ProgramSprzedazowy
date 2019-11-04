#include "saleswindow.h"
#include "ui_saleswindow.h"

salesWindow::salesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salesWindow)
{
    ui->setupUi(this);
    fillComboBox();
}

salesWindow::~salesWindow()
{
    delete ui;
}

void salesWindow::on_button_return_clicked()
{
    salesWindow::close();
}

void salesWindow::fillComboBox(){
    sql conn;
    conn.dbOpen();
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("select * from kontrahenci where id>2"); //nie interesuje nas PARAGON ani DOSTAWA
    query->exec();

    ui->comboBox->clear();
    ui->comboBox->addItem("");

    query->seek(-1);
    while(query->next()){
        ui->comboBox->addItem(query->value(1).toString());
    }

    conn.dbClose();
}

void salesWindow::on_button_contiune_clicked()
{
    QString comboText = ui->comboBox->currentText();
    if( comboText!="" ){
        salesCreate salesCreate;
        salesCreate.createInvoice(comboText);
        salesCreate.setModal(true);
        salesCreate.exec();
        salesWindow::close();
    }else{
        qDebug() << "Niepoprawny wybór!";
    }
}

void salesWindow::on_button_quickSell_clicked()
{
    salesCreate salesCreate;
    salesCreate.createInvoice("PARAGON");
    salesCreate.setModal(true);
    salesCreate.exec();
    salesWindow::close();
}
