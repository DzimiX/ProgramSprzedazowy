#ifndef STORAGEWINDOW_H
#define STORAGEWINDOW_H

#include <QDialog>

namespace Ui {
class storageWindow;
}

class storageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit storageWindow(QWidget *parent = nullptr);
    ~storageWindow();

private:
    Ui::storageWindow *ui;
};

#endif // STORAGEWINDOW_H
