#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"

class Customer : public User {
private:
    std::string deliveryAddress;
    int loyaltyPoints;

public:
    Customer();
    Customer(const std::string& uid, const std::string& n,
             const std::string& phone, const std::string& address,
             int points = 0);

    void   displayInfo()       const override;
    double calculateEarnings() const override;

    std::string getDeliveryAddress() const;
    int         getLoyaltyPoints()   const;

    void setDeliveryAddress(const std::string& address);
    void setLoyaltyPoints(int points);

    Customer& operator+=(int points);
};

#endif // CUSTOMER_H
