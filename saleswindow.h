#ifndef SALESWINDOW_H
#define SALESWINDOW_H

#include <QDialog>
#include "sql.h"
#include "salescreate.h"

namespace Ui {
class salesWindow;
}

class salesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit salesWindow(QWidget *parent = nullptr);
    ~salesWindow();

private slots:
    void on_button_return_clicked();

    void on_button_contiune_clicked();

    void on_button_quickSell_clicked();

private:
    Ui::salesWindow *ui;

public:
    void fillComboBox();
};

#endif // SALESWINDOW_H
