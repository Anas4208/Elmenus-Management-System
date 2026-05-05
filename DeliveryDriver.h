// DeliveryDriver.h
#ifndef DELIVERYDRIVER_H
#define DELIVERYDRIVER_H

#include "User.h"

class DeliveryDriver : public User {
private:
    std::string vehicleType;
    int         completedDeliveries;
    double      totalEarnings;

public:
    DeliveryDriver();
    DeliveryDriver(const std::string& uid, const std::string& n,
                   const std::string& phone, const std::string& vehicle);

    // ✅ Rule of 5: complete all 5 — copy was missing, move was already here
    DeliveryDriver(const DeliveryDriver& other)            = default;
    DeliveryDriver& operator=(const DeliveryDriver& other) = default;
    DeliveryDriver(DeliveryDriver&& other)            noexcept = default;
    DeliveryDriver& operator=(DeliveryDriver&& other) noexcept = default;
    ~DeliveryDriver() override = default;

    void   displayInfo()       const override;
    double calculateEarnings() const override;

    void completeDelivery(double orderValue);

    DeliveryDriver& operator++();      // prefix
    DeliveryDriver  operator++(int);   // postfix

    std::string getVehicleType()         const;
    int         getCompletedDeliveries() const;
    double      getTotalEarnings()       const;
};

#endif // DELIVERYDRIVER_H