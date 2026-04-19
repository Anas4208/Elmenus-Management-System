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
    ~DeliveryDriver() override;
    
    DeliveryDriver(const DeliveryDriver& other);
    DeliveryDriver& operator=(const DeliveryDriver& other);
    DeliveryDriver(DeliveryDriver&& other) noexcept;
    DeliveryDriver& operator=(DeliveryDriver&& other) noexcept;
    
    void displayInfo() const override;
    double calculateEarnings() const override;
    
    void completeDelivery(double orderValue);
    
    DeliveryDriver& operator++();
    DeliveryDriver operator++(int);
    
    int getCompletedDeliveries() const;
    double getTotalEarnings() const;
};

#endif
