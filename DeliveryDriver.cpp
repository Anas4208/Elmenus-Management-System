// DeliveryDriver.cpp
#include "DeliveryDriver.h"
#include <iostream>
#include <iomanip>

DeliveryDriver::DeliveryDriver()
    : User(), vehicleType(""), completedDeliveries(0), totalEarnings(0.0) {}

DeliveryDriver::DeliveryDriver(const std::string& uid, const std::string& n,
                               const std::string& phone, const std::string& vehicle)
    : User(uid, n, phone), vehicleType(vehicle),
      completedDeliveries(0), totalEarnings(0.0) {}

void DeliveryDriver::displayInfo() const {
    double avg = (completedDeliveries > 0)
                     ? totalEarnings / static_cast<double>(completedDeliveries)
                     : 0.0;
    std::cout << std::fixed << std::setprecision(2)
              << "=== Driver Info ===\n"
              << "ID          : " << getUserId()          << "\n"  // ✅ getter
              << "Name        : " << getName()             << "\n"  // ✅ getter
              << "Phone       : " << getPhoneNumber()      << "\n"  // ✅ getter
              << "Vehicle     : " << vehicleType           << "\n"
              << "Deliveries  : " << completedDeliveries   << "\n"
              << "Earnings    : " << totalEarnings         << " EGP\n"
              << "Avg/Delivery: " << avg                   << " EGP\n";
}

double DeliveryDriver::calculateEarnings() const { return totalEarnings; }

void DeliveryDriver::completeDelivery(double orderValue) {
    totalEarnings += orderValue * 0.15;
}

DeliveryDriver& DeliveryDriver::operator++() {
    ++completedDeliveries;
    return *this;
}

DeliveryDriver DeliveryDriver::operator++(int) {
    DeliveryDriver tmp = *this;   // uses copy constructor (now explicitly = default)
    ++completedDeliveries;
    return tmp;
}

std::string DeliveryDriver::getVehicleType()         const { return vehicleType;         }
int         DeliveryDriver::getCompletedDeliveries() const { return completedDeliveries; }
double      DeliveryDriver::getTotalEarnings()       const { return totalEarnings;       }