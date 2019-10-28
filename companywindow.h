#ifndef COMPANYWINDOW_H
#define COMPANYWINDOW_H

#include <QDialog>

namespace Ui {
class companyWindow;
}

class companyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit companyWindow(QWidget *parent = nullptr);
    ~companyWindow();

private:
    Ui::companyWindow *ui;
};

#endif // COMPANYWINDOW_H
