#include "editclients.h"
#include "ui_editclients.h"

editClients::editClients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editClients)
{
    ui->setupUi(this);
}

editClients::~editClients()
{
    delete ui;
}

void editClients::on_button_update_clicked()
{

}

void editClients::on_button_return_clicked()
{
    editClients::close();
}
