#include "Customer.h"
#include <iostream>

Customer::Customer() : User(), deliveryAddress_("") {}

Customer::Customer(const std::string& id, const std::string& name, 
                   const std::string& phone, const std::string& address)
    : User(id, name, phone), deliveryAddress_(address) {}

void Customer::displayInfo() const {
    std::cout << "\n=== Customer Information ===" << std::endl;
    std::cout << "ID: " << getUserId() << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Phone: " << getPhoneNumber() << std::endl;
    std::cout << "Address: " << deliveryAddress_ << std::endl;
    std::cout << "Loyalty Points: " << loyaltyPoints_ << std::endl;
    std::cout << "===========================" << std::endl;
}

double Customer::calculateEarnings() const {
    return static_cast<double>(loyaltyPoints_) * 0.5;
}

void Customer::setLoyaltyPoints(int points) {
    loyaltyPoints_ = (points >= 0) ? points : 0;
}

int Customer::getLoyaltyPoints() const {
    return loyaltyPoints_;
}

Customer& Customer::operator+=(int points) {
    if (points > 0) {
        loyaltyPoints_ += points;
    }
    return *this;
}
