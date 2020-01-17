#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "saleswindow.h"
#include "supplieswindow.h"
#include "clientswindow.h"
#include "productswindow.h"
#include "companywindow.h"
#include "storagewindow.h"
#include "salesview.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow();
    ~mainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

    void on_comboBox_activated();

private:
    Ui::mainWindow *ui;
    void updateStaticText();
};

#endif // MAINWINDOW_H
