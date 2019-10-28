#include "entrywindow.h"
#include "ui_entrywindow.h"

entryWindow::entryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::entryWindow)
{
    ui->setupUi(this);
}

entryWindow::~entryWindow()
{
    delete ui;
}

