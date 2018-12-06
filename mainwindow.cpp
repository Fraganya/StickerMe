#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(400,400);

    //initialize signals and slots
    connect(ui->btnSaveOrder,SIGNAL(clicked(bool)),this,SLOT(saveOrder()));
    connect(ui->btnSeeOrders,SIGNAL(clicked()),this,SLOT(seeOrders()));

    this->connectDB();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDB()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("sticker_me");
    db.setUserName("root");
    db.setPassword("");

    if(!db.isOpen()){
        if(!db.open()){
            QMessageBox::critical(this,"DB Error",db.lastError().text());
        }
    }
}

void MainWindow::resetData()
{
    this->ui->txtCustomerName->clear();
    this->ui->txtOrderDetails->clear();

    this->ui->cbxDelivered->setChecked(false);
    this->ui->cbxHasPaid->setChecked(false);
}

void MainWindow::seeOrders()
{
    OrdersWindow * ordersWin = new OrdersWindow(this);
    ordersWin->show();
}

void MainWindow::saveOrder()
{
    QString name=this->ui->txtCustomerName->text().trimmed();
    QString details=this->ui->txtOrderDetails->toPlainText().trimmed();


    int has_paid = false;
    int delivered = false;

    if(this->ui->cbxHasPaid->isChecked()){
        has_paid = 1;
    }

    if(this->ui->cbxDelivered->isChecked()){
        delivered = 1;
    }


    Order * newOrder = new Order();
    newOrder->setProps(name,details,has_paid,delivered);
    //validate
    if(!newOrder->isValid()){
        QMessageBox::critical(this,"Aborted","Some fields are empty!");
        return;
    }

    //execute query
    QSqlQuery query = newOrder->makeQuery();

    if(!query.exec()){
         QMessageBox::critical(this,"DB Error",query.lastError().text());
         return;
    }

    QMessageBox::information(this,"Success","Order has been saved");

    this->resetData();
}
