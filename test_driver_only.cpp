#include "DeliveryDriver.h"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "\n=== Testing DeliveryDriver ===" << std::endl;
    
    // Test 1: Default constructor
    DeliveryDriver d1;
    assert(d1.getCompletedDeliveries() == 0);
    assert(d1.getTotalEarnings() == 0.0);
    std::cout << "✅ Default constructor works" << std::endl;
    
    // Test 2: Parameterized constructor
    DeliveryDriver d2("D001", "Bob Driver", "5551234567", "Van", 5, 100.0);
    assert(d2.getUserId() == "D001");
    assert(d2.getName() == "Bob Driver");
    assert(d2.getCompletedDeliveries() == 5);
    assert(d2.getTotalEarnings() == 100.0);
    std::cout << "✅ Parameterized constructor works" << std::endl;
    
    // Test 3: completeDelivery (15% commission)
    d2.completeDelivery(100.0);
    assert(d2.getTotalEarnings() == 115.0); // 100 + 15
    std::cout << "✅ completeDelivery works (15% commission)" << std::endl;
    
    // Test 4: Prefix increment (++driver)
    ++d2;
    assert(d2.getCompletedDeliveries() == 6);
    std::cout << "✅ Prefix increment works" << std::endl;
    
    // Test 5: Postfix increment (driver++)
    d2++;
    assert(d2.getCompletedDeliveries() == 7);
    std::cout << "✅ Postfix increment works" << std::endl;
    
    // Test 6: calculateEarnings
    assert(d2.calculateEarnings() == 115.0);
    std::cout << "✅ calculateEarnings works" << std::endl;
    
    // Test 7: Display info
    d2.displayInfo();
    std::cout << "✅ displayInfo works" << std::endl;
    
    // Test 8: Negative order value handling
    try {
        d2.completeDelivery(-50.0);
        std::cout << "❌ Should have thrown exception for negative value" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "✅ Negative value correctly rejected" << std::endl;
    }
    
    // Test 9: Multiple deliveries
    DeliveryDriver d3;
    for (int i = 0; i < 10; i++) {
        d3.completeDelivery(100.0);
        ++d3;
    }
    assert(d3.getCompletedDeliveries() == 10);
    assert(d3.getTotalEarnings() == 150.0); // 10 * 15 = 150
    std::cout << "✅ Multiple deliveries tracked correctly" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "ALL DELIVERYDRIVER TESTS PASSED! 🎉" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}
