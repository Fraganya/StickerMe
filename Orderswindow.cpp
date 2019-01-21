#include "Orderswindow.h"
#include "ui_Orderswindow.h"

OrdersWindow::OrdersWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrdersWindow)
{
    ui->setupUi(this);

    connect(ui->btnUpdate,SIGNAL(clicked(bool)),this,SLOT(updateOrder()));
    this->initData();
}

OrdersWindow::~OrdersWindow()
{
    delete ui;
}

void OrdersWindow::initData()
{
    QSqlQueryModel * ordersModel=new QSqlQueryModel(this);
    ordersModel->setQuery(QSqlQuery("select id,name,details,has_paid,delivered from orders"));
    ui->tblOrders->setModel(ordersModel);
    ui->tblOrders->resizeRowsToContents();
    //set proper header names
    ordersModel->setHeaderData(0,Qt::Horizontal,tr("ID"));
    ordersModel->setHeaderData(1,Qt::Horizontal,tr("Customer"));
    ordersModel->setHeaderData(2,Qt::Horizontal,tr("Details"));
    ordersModel->setHeaderData(3,Qt::Horizontal,tr("Paid"));
    ordersModel->setHeaderData(4,Qt::Horizontal,tr("Delivered"));

    //adjust horizontal header to take full space
    QHeaderView * header=ui->tblOrders->horizontalHeader();
    for(int col=0;col<header->count();col++)
    {
        header->setSectionResizeMode(col,QHeaderView::Stretch);
    }
}

void OrdersWindow::updateModel()
{
    this->initData();

    ui->txtOrderNum->clear();
    ui->cbxDelivered->setChecked(false);
    ui->cbxPaid->setChecked(false);
}

void OrdersWindow::updateOrder()
{
    bool * status = new bool;
    int orderNum = ui->txtOrderNum->text().trimmed().toInt(status);

    if(*status != true){
        QMessageBox::critical(this,"Error","The order number must be a valid numeric value");
        return;
    }

    QSqlQuery query;

    if(ui->cbxDelivered->isChecked() && ui->cbxPaid->isChecked())
    {
        query.prepare("UPDATE orders set has_paid=1,delivered=1 WHERE id=?");
    }
    else if(ui->cbxDelivered->isChecked()){
         query.prepare("UPDATE orders set delivered=1 WHERE id=?");
    }
    else if(ui->cbxPaid->isChecked()){
         query.prepare("UPDATE orders set has_paid=1 WHERE id=?");
    }
    else{
        QMessageBox::critical(this,"Error","There is nothing to update");
        return;
    }

    query.addBindValue(orderNum);

    if(!query.exec()){
         QMessageBox::critical(this,"DB Error",query.lastError().text());
         return;
    }

    QMessageBox::information(this,"Success","Order has been saved");

    this->updateModel();

}
