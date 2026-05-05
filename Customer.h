// Customer.h
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"

class Customer : public User {
private:
    std::string deliveryAddress;
    int         loyaltyPoints;

public:
    Customer();
    Customer(const std::string& uid, const std::string& n,
             const std::string& phone, const std::string& address,
             int points = 0);

    // ✅ Rule of 5: explicit copy/move since base class defines them
    Customer(const Customer& other)            = default;
    Customer& operator=(const Customer& other) = default;
    Customer(Customer&& other)            noexcept = default;
    Customer& operator=(Customer&& other) noexcept = default;

    ~Customer() override = default;

    void   displayInfo()       const override;
    double calculateEarnings() const override;

    std::string getDeliveryAddress() const;
    int         getLoyaltyPoints()   const;

    void setDeliveryAddress(const std::string& address);
    void setLoyaltyPoints(int points);

    Customer& operator+=(int points);
};

#endif // CUSTOMER_H