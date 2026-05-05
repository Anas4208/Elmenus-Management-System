#ifndef DELIVERYDRIVER_H
#define DELIVERYDRIVER_H

#include "User.h"

class DeliveryDriver : public User {
private:
    std::string vehicleType;
    int    completedDeliveries;
    double totalEarnings;

public:
    DeliveryDriver();
    DeliveryDriver(const std::string& uid, const std::string& n,
                const std::string& phone, const std::string& vehicle);
                
    DeliveryDriver(DeliveryDriver&& other) noexcept = default;
    DeliveryDriver& operator=(DeliveryDriver&& other) noexcept = default;
    void   displayInfo()       const override;
    double calculateEarnings() const override;

    void completeDelivery(double orderValue);

    // prefix ++
    DeliveryDriver& operator++();
    // postfix ++
    DeliveryDriver  operator++(int);

    std::string getVehicleType()         const;
    int         getCompletedDeliveries() const;
    double      getTotalEarnings()       const;
};

#endif // DELIVERYDRIVER_H
