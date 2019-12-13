#ifndef STORAGEWINDOW_H
#define STORAGEWINDOW_H

#include <QDialog>
#include "sql.h"

namespace Ui {
class storageWindow;
}

class storageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit storageWindow(QWidget *parent = nullptr);
    ~storageWindow();

private slots:
    void on_button_return_clicked();

private:
    Ui::storageWindow *ui;

public:
    void updateDetails();
};

#endif // STORAGEWINDOW_H
