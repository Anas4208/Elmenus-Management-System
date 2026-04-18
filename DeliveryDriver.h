/*Anas Mohamed gamal 20246022
Ziad Gawad 20246055
group G6*/
#ifndef DELIVERYDRIVER_H
#define DELIVERYDRIVER_H
#include "User.h"

class DeliveryDriver :public User{
    private:
    string vehicleType;
    int completedDeliveries;
    double totalEarnings;
    public:
    DeliveryDriver();
    DeliveryDriver(string id, string n, string p, string v, int c, double t);
    void displayInfo();
    double calculateEarnings();
    void completeDelivery(double ordervalue);
    //prefix overload
    DeliveryDriver &operator++();
    //postfix overload dummy parameter
    DeliveryDriver operator++(int);
    int getCompletedDeliveries() const;
    double getTotalEarnings() const;
};
#endif