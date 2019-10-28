#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include <QDialog>

namespace Ui {
class clientsWindow;
}

class clientsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit clientsWindow(QWidget *parent = nullptr);
    ~clientsWindow();

private:
    Ui::clientsWindow *ui;
};

#endif // CLIENTSWINDOW_H
