#ifndef SALESVIEW_H
#define SALESVIEW_H

#include <QDialog>
#include "sql.h"
#include "salesdetail.h"

namespace Ui {
class salesView;
}

class salesView : public QDialog
{
    Q_OBJECT

public:
    explicit salesView(QWidget *parent = nullptr);
    ~salesView();
    void updateDisplay();
    void updateComboBox();

private slots:
    void on_button_return_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_button_details_clicked();

private:
    Ui::salesView *ui;
};

#endif // SALESVIEW_H
