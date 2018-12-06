#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QInputDialog>

#include "order.h"
#include "Orderswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void connectDB();
    void resetData();


private slots:
   void saveOrder();
   void seeOrders();
};

#endif // MAINWINDOW_H
