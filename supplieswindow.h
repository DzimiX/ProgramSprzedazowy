#ifndef SUPPLIESWINDOW_H
#define SUPPLIESWINDOW_H

#include <QDialog>

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
};

#endif // SUPPLIESWINDOW_H
