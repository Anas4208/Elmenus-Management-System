/*Anas Mohamed gamal 20246022
Ziad Gawad 20246055
group G6*/
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "User.h"

class Customer :public User {
    private:
    string deliveryAddress;
    int loyaltyPoints;
    public:
    Customer();
    Customer(string id, string n, string p, string a);
    void displayInfo();
    double calculateEarnings();
    void setLoyaltyPoints(int p);
    int getLoyaltyPoints() const;
    Customer &operator+=(int p);
};
#endif