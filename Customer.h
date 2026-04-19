#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <string>

class Customer : public User {
private:
    std::string deliveryAddress_;
    int loyaltyPoints_{0};
    
public:
    Customer();
    explicit Customer(const std::string& id, const std::string& name, 
                      const std::string& phone, const std::string& address);
    ~Customer() override = default;
    
    void displayInfo() const override;
    double calculateEarnings() const override;
    
    void setLoyaltyPoints(int points);
    int getLoyaltyPoints() const;
    
    Customer& operator+=(int points);
};

#endif
