#ifndef DELIVERYDRIVER_H
#define DELIVERYDRIVER_H

#include "User.h"
#include <string>
#include <climits>

class DeliveryDriver : public User {
private:
    std::string vehicleType_;
    int completedDeliveries_;
    double totalEarnings_;
    
public:
    DeliveryDriver();
    explicit DeliveryDriver(const std::string& id, const std::string& name, 
                           const std::string& phone, const std::string& vehicleType,
                           int completedDeliveries = 0, double totalEarnings = 0.0);
    
    // Allow copy and move operations
    DeliveryDriver(const DeliveryDriver& other) = default;
    DeliveryDriver& operator=(const DeliveryDriver& other) = default;
    DeliveryDriver(DeliveryDriver&& other) noexcept = default;
    DeliveryDriver& operator=(DeliveryDriver&& other) noexcept = default;
    
    void displayInfo() const override;
    double calculateEarnings() const override;
    
    void completeDelivery(double orderValue);
    
    // Prefix increment (++driver)
    DeliveryDriver& operator++();
    // Postfix increment (driver++)
    DeliveryDriver operator++(int);
    
    // Getters
    int getCompletedDeliveries() const;
    double getTotalEarnings() const;
    
    virtual ~DeliveryDriver() = default;
};

#endif