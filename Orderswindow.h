#ifndef ORDERSWINDOW_H
#define ORDERSWINDOW_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class OrdersWindow;
}

class OrdersWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OrdersWindow(QWidget *parent = 0);

    ~OrdersWindow();

private:
    Ui::OrdersWindow *ui;
    void initData();
    void updateModel();


private slots:
    void updateOrder();

};

#endif // ORDERSWINDOW_H
