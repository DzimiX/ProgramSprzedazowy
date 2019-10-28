#ifndef SALESWINDOW_H
#define SALESWINDOW_H

#include <QDialog>

namespace Ui {
class salesWindow;
}

class salesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit salesWindow(QWidget *parent = nullptr);
    ~salesWindow();

private:
    Ui::salesWindow *ui;
};

#endif // SALESWINDOW_H
