#ifndef PRODUCTSWINDOW_H
#define PRODUCTSWINDOW_H

#include <QDialog>

namespace Ui {
class productsWindow;
}

class productsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit productsWindow(QWidget *parent = nullptr);
    ~productsWindow();

private:
    Ui::productsWindow *ui;
};

#endif // PRODUCTSWINDOW_H
