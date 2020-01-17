#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow() :
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->comboBox->addItem("Motyw");
    ui->comboBox->addItem("Jasny");
    ui->comboBox->addItem("Ciemny");

    updateStaticText();
}

mainWindow::~mainWindow()
{
    delete ui;
    QApplication::quit();
}

void mainWindow::on_pushButton_clicked()
{
    salesWindow* salesWindow = new class salesWindow;
    salesWindow->setModal(true);
    salesWindow->exec();
    delete salesWindow;
}

void mainWindow::on_pushButton_2_clicked()
{
    suppliesWindow suppliesWindow;
    suppliesWindow.setModal(true);
    suppliesWindow.exec();
}

void mainWindow::on_pushButton_3_clicked()
{
    clientsWindow clientsWindow;
    clientsWindow.setModal(true);
    clientsWindow.exec();
}

void mainWindow::on_pushButton_4_clicked()
{
    productsWindow productsWindow;
    productsWindow.setModal(true);
    productsWindow.exec();
}

void mainWindow::on_pushButton_5_clicked()
{
    companyWindow companyWindow;
    companyWindow.setModal(true);
    companyWindow.exec();
    updateStaticText();
}

void mainWindow::updateStaticText(){
    sql conn;
    conn.dbOpen(conn.location);
    QSqlQuery *query = new QSqlQuery(conn.db);

    query->prepare("SELECT * FROM firma");
    query->exec();

    query->seek(-1);
    query->next();
    ui->company_name->setText(query->value(0).toString());

    if(query->value(11).toString()=="Ciemny"){
        QFile f(":qdarkstyle/style.qss");
        if (!f.exists())
        {
            printf("Unable to set stylesheet, file not found\n");
        }
        else
        {
            f.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&f);
            qApp->setStyleSheet(ts.readAll());
        }
    }else{
        qApp->setStyleSheet(nullptr);
    }

    conn.dbClose();
}

void mainWindow::on_pushButton_6_clicked()
{
    storageWindow storageWindow;
    storageWindow.setModal(true);
    storageWindow.exec();
}

void mainWindow::on_pushButton_7_clicked()
{
    salesView salesView;
    salesView.setModal(true);
    salesView.exec();
}

void mainWindow::on_comboBox_activated()
{
    if(ui->comboBox->currentText()!="Motyw"){
        sql conn;
        conn.dbOpen(conn.location);
        QSqlQuery *query = new QSqlQuery(conn.db);
        query->prepare("UPDATE firma SET motyw=:motyw WHERE 1=1; ");
        query->bindValue(":motyw", ui->comboBox->currentText());
        query->exec();
        conn.dbClose();
        updateStaticText();
    }
}
