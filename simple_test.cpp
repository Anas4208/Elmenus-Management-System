#include "Customer.h"
#include "DeliveryDriver.h"
#include "User.h"
#include <iostream>

int main() {
    std::cout << "=== Running Simple Tests ===\n" << std::endl;
    
    // Test Customer
    std::cout << "1. Testing Customer..." << std::endl;
    Customer c1("C001", "John Doe", "123456", "123 Main St");
    c1.displayInfo();
    c1.setLoyaltyPoints(100);
    c1 += 50;
    std::cout << "Loyalty points after +=50: " << c1.getLoyaltyPoints() << std::endl;
    std::cout << "Earnings: " << c1.calculateEarnings() << std::endl;
    
    // Test DeliveryDriver
    std::cout << "\n2. Testing DeliveryDriver..." << std::endl;
    DeliveryDriver d1("D001", "Bob Driver", "555123", "Van", 5, 100.0);
    d1.displayInfo();
    d1.completeDelivery(100.0);
    std::cout << "After delivery: " << d1.getTotalEarnings() << std::endl;
    ++d1;
    d1++;
    std::cout << "Deliveries after increments: " << d1.getCompletedDeliveries() << std::endl;
    
    // Test User static counter
    std::cout << "\n3. Testing User counter..." << std::endl;
    std::cout << "Total users: " << User::getTotalUsers() << std::endl;
    
    std::cout << "\n=== All tests completed! ===" << std::endl;
    return 0;
}
