#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class entryWindow; }
QT_END_NAMESPACE

class entryWindow : public QMainWindow
{
    Q_OBJECT

public:
    entryWindow(QWidget *parent = nullptr);
    ~entryWindow();

private:
    Ui::entryWindow *ui;
};
#endif // ENTRYWINDOW_H
