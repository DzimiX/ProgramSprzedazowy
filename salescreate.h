#ifndef SALESCREATE_H
#define SALESCREATE_H

#include <QDialog>

namespace Ui {
class salesCreate;
}

class salesCreate : public QDialog
{
    Q_OBJECT

public:
    explicit salesCreate(QWidget *parent = nullptr);
    ~salesCreate();

private slots:
    void on_button_quit_clicked();

private:
    Ui::salesCreate *ui;
};

#endif // SALESCREATE_H
