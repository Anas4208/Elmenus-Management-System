#include "Customer.h"
#include <iostream>

Customer::Customer()
    : User(), deliveryAddress(""), loyaltyPoints(0) {}

Customer::Customer(const std::string& uid, const std::string& n,
                   const std::string& phone, const std::string& address,
                   int points)
    : User(uid, n, phone), deliveryAddress(address), loyaltyPoints(points) {}

void Customer::displayInfo() const {
    std::cout << "=== Customer Info ===\n"
              << "ID      : " << userId      << "\n"
              << "Name    : " << name        << "\n"
              << "Phone   : " << phoneNumber << "\n"
              << "Address : " << deliveryAddress << "\n"
              << "Loyalty : " << loyaltyPoints   << " pts\n";
}

double Customer::calculateEarnings() const {
    return static_cast<double>(loyaltyPoints) * 0.5;
}

std::string Customer::getDeliveryAddress() const { return deliveryAddress; }
int         Customer::getLoyaltyPoints()   const { return loyaltyPoints;   }

void Customer::setDeliveryAddress(const std::string& address) {
    deliveryAddress = address;
}
void Customer::setLoyaltyPoints(int points) { loyaltyPoints = points; }

Customer& Customer::operator+=(int points) {
    loyaltyPoints += points;
    return *this;
}
