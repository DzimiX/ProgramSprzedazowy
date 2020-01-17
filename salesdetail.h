#ifndef SALESDETAIL_H
#define SALESDETAIL_H

#include <QMessageBox>

#include "sql.h"

namespace Ui {
class salesDetail;
}

class salesDetail : public QDialog
{
    Q_OBJECT

public slots:

    void updateDetails();

public:
    static int invoiceId;
    explicit salesDetail(QWidget *parent = nullptr);
    ~salesDetail();

private slots:
    void on_button_return_clicked();

    void on_button_cancel_clicked();

    void on_button_print_clicked();

private:
    Ui::salesDetail *ui;
};



#endif // SALESDETAIL_H
