#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include <QDialog>
#include <QSql>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include "sql.h"
#include "addclients.h"
#include "editclients.h"

namespace Ui {
class clientsWindow;
}

class clientsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit clientsWindow(QWidget *parent = nullptr);
    ~clientsWindow();

private:
    Ui::clientsWindow *ui;

public:
    void updateClientsList();
private slots:
    void on_button_newClient_clicked();
    void on_button_editSelected_clicked();
    void on_button_removeSelected_clicked();
    void on_button_return_clicked();
    void on_tableView_clicked();
};

#endif // CLIENTSWINDOW_H
