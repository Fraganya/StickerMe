#include "Orderswindow.h"
#include "ui_Orderswindow.h"

OrdersWindow::OrdersWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrdersWindow)
{
    ui->setupUi(this);

    this->initData();
}

OrdersWindow::~OrdersWindow()
{
    delete ui;
}

void OrdersWindow::initData()
{
    QSqlQueryModel * ordersModel=new QSqlQueryModel(this);
    ordersModel->setQuery(QSqlQuery("select name,details,has_paid,delivered from orders"));
    ui->tblOrders->setModel(ordersModel);
    ui->tblOrders->resizeRowsToContents();
    //set proper header names
    ordersModel->setHeaderData(0,Qt::Horizontal,tr("Customer"));
    ordersModel->setHeaderData(1,Qt::Horizontal,tr("Details"));
    ordersModel->setHeaderData(2,Qt::Horizontal,tr("Paid"));
    ordersModel->setHeaderData(3,Qt::Horizontal,tr("Delivered"));

    //adjust horizontal header to take full space
    QHeaderView * header=ui->tblOrders->horizontalHeader();
    for(int col=0;col<header->count();col++)
    {
        header->setSectionResizeMode(col,QHeaderView::Stretch);
    }
}
