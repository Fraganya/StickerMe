#include "order.h"

Order::Order()
{

}

bool Order::isValid()
{
    if(this->name.isEmpty() || this->details.isEmpty()){
        return false;
    }

    return true;
}

void Order::setProps(QString name, QString details, int paid, int delivered)
{
    this->name=name;
    this->details=details;
    this->has_paid=paid;
    this->delivered=delivered;
}

QSqlQuery  Order::makeQuery()
{
    QSqlQuery query;
    query.prepare("INSERT INTO orders (name,details,has_paid,delivered) VALUES(?,?,?,?)");
    query.addBindValue(this->name);
    query.addBindValue(this->details);
    query.addBindValue(this->has_paid);
    query.addBindValue(this->delivered);

    return query;
}
