#ifndef ORDER_H
#define ORDER_H

#include <QtSql>

class Order
{
public:
    Order();

    bool isValid();
    void setProps(QString,QString,int,int);
    QSqlQuery makeQuery();
private:
   QString name;
   QString details;
   int has_paid;
   int delivered;
};

#endif // ORDER_H
