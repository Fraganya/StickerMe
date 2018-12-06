#ifndef ORDERSWINDOW_H
#define ORDERSWINDOW_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class OrdersWindow;
}

class OrdersWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OrdersWindow(QWidget *parent = 0);
     void initData();
    ~OrdersWindow();

private:
    Ui::OrdersWindow *ui;

};

#endif // ORDERSWINDOW_H
