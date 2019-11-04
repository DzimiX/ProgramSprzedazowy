#ifndef SALESVIEW_H
#define SALESVIEW_H

#include <QDialog>

namespace Ui {
class salesView;
}

class salesView : public QDialog
{
    Q_OBJECT

public:
    explicit salesView(QWidget *parent = nullptr);
    ~salesView();

private slots:
    void on_button_return_clicked();

private:
    Ui::salesView *ui;
};

#endif // SALESVIEW_H
