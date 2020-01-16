#ifndef SUPPLIESWINDOW_H
#define SUPPLIESWINDOW_H

#include <QDialog>
#include "sql.h"
#include "salescreate.h"
#include "salesdetail.h"

namespace Ui {
class suppliesWindow;
}

class suppliesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit suppliesWindow(QWidget *parent = nullptr);
    ~suppliesWindow();

private:
    Ui::suppliesWindow *ui;
public:
    void updateDetails();
    void updateComboBox();
private slots:
    void on_button_return_clicked();
    void on_newSupply_clicked();
    void on_tableView_clicked();
    void on_editSupply_clicked();
};

#endif // SUPPLIESWINDOW_H
