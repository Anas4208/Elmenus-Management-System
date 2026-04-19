#include "DeliveryDriver.h"
#include <iostream>
#include <stdexcept>
#include <climits>
#include <iomanip>

DeliveryDriver::DeliveryDriver() 
    : User(), vehicleType_(""), completedDeliveries_(0), totalEarnings_(0.0) {}

DeliveryDriver::DeliveryDriver(const std::string& id, const std::string& name, 
                               const std::string& phone, const std::string& vehicleType,
                               int completedDeliveries, double totalEarnings)
    : User(id, name, phone), vehicleType_(vehicleType), 
      completedDeliveries_(completedDeliveries), totalEarnings_(totalEarnings) {
    if (completedDeliveries_ < 0) completedDeliveries_ = 0;
    if (totalEarnings_ < 0) totalEarnings_ = 0;
}

void DeliveryDriver::displayInfo() const {
    std::cout << "\n=== Driver Information ===" << std::endl;
    std::cout << "ID: " << getUserId() << std::endl;  // Using getter
    std::cout << "Name: " << getName() << std::endl;  // Using getter
    std::cout << "Phone: " << getPhoneNumber() << std::endl;  // Using getter
    std::cout << "Vehicle: " << vehicleType_ << std::endl;
    std::cout << "Completed Deliveries: " << completedDeliveries_ << std::endl;
    std::cout << "Total Earnings: " << std::fixed << std::setprecision(2) 
              << totalEarnings_ << " EGP" << std::endl;
    
    if (completedDeliveries_ > 0) {
        double average = totalEarnings_ / completedDeliveries_;
        std::cout << "Average per Delivery: " << std::fixed << std::setprecision(2) 
                  << average << " EGP" << std::endl;
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

DeliveryDriver& DeliveryDriver::operator++() {
    if (completedDeliveries_ < INT_MAX) {
        completedDeliveries_++;
    }
    return *this;
}

DeliveryDriver DeliveryDriver::operator++(int) {
    DeliveryDriver temp = *this;
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
