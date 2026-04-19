#include "DeliveryDriver.h"
#include <iostream>
#include <stdexcept>
#include <climits>

DeliveryDriver::DeliveryDriver() 
    : User(), vehicleType_(""), completedDeliveries_(0), totalEarnings_(0.0) {}

DeliveryDriver::DeliveryDriver(const std::string& id, const std::string& name, 
                               const std::string& phone, const std::string& vehicleType,
                               int completedDeliveries, double totalEarnings) 
    : User(id, name, phone), vehicleType_(vehicleType), 
      completedDeliveries_(completedDeliveries), totalEarnings_(totalEarnings) {}

void DeliveryDriver::displayInfo() const {
    std::cout << "=== Driver Information ===" << std::endl;
    std::cout << "ID: " << getUserId() << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Phone: " << getPhoneNumber() << std::endl;
    std::cout << "Vehicle Type: " << vehicleType_ << std::endl;
    std::cout << "Completed Deliveries: " << completedDeliveries_ << std::endl;
    std::cout << "Total Earnings: $" << totalEarnings_ << std::endl;
    
    if (completedDeliveries_ > 0) {
        double averageEarning = totalEarnings_ / completedDeliveries_;
        std::cout << "Average per Delivery: $" << averageEarning << std::endl;
    }
    std::cout << "===========================" << std::endl;
}

double DeliveryDriver::calculateEarnings() const {
    return totalEarnings_;
}

void DeliveryDriver::completeDelivery(double orderValue) {
    if (orderValue < 0) {
        throw std::invalid_argument("Order value cannot be negative");
    }
    constexpr double COMMISSION_RATE = 0.15;
    totalEarnings_ += COMMISSION_RATE * orderValue;
}

// Prefix increment (++driver)
DeliveryDriver& DeliveryDriver::operator++() {
    if (completedDeliveries_ < INT_MAX) {
        completedDeliveries_++;
    }
    return *this;
}

// Postfix increment (driver++)
DeliveryDriver DeliveryDriver::operator++(int) {
    // Create a copy using the copy constructor
    DeliveryDriver temp = *this;  // Now this works because copy constructor is defaulted
    if (completedDeliveries_ < INT_MAX) {
        completedDeliveries_++;
    }
    return temp;
}

int DeliveryDriver::getCompletedDeliveries() const {
    return completedDeliveries_;
}

double DeliveryDriver::getTotalEarnings() const {
    return totalEarnings_;
}