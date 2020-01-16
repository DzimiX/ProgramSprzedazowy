#ifndef COMPANYWINDOW_H
#define COMPANYWINDOW_H

#include "sql.h"

namespace Ui {
class companyWindow;
}

class companyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit companyWindow(QWidget *parent = nullptr);
    ~companyWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::companyWindow *ui;
};

#endif // COMPANYWINDOW_H
