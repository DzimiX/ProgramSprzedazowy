#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class entryWindow; }
QT_END_NAMESPACE

class entryWindow : public QMainWindow
{
    Q_OBJECT

public:
    entryWindow(QWidget *parent = nullptr);
    ~entryWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::entryWindow *ui;
    mainWindow *mainWindow;
};
#endif // ENTRYWINDOW_H
