#include "FileOps.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void saveCompletedOrders(const std::vector<Order*>& orders) {
    std::ofstream file("completed_orders.txt");
    if (!file.is_open()) {
        std::cerr << "Error: cannot open completed_orders.txt\n";
        return;
    }

    bool anyDelivered = false;
    for (const Order* order : orders) {
        if (order != nullptr && order->getStatus() == OrderStatus::DELIVERED) {
            anyDelivered = true;
            // Write to screen and file
            std::cout << *order;
            file    << *order;
        }
    }

    if (!anyDelivered) {
        std::cout << "No completed orders to save.\n";
    }

    file.close();
    std::cout << "Completed orders saved to completed_orders.txt\n";
}

void saveDriverStats(const std::vector<DeliveryDriver*>& drivers) {
    std::ofstream file("driver_stats.txt");
    if (!file.is_open()) {
        std::cerr << "Error: cannot open driver_stats.txt\n";
        return;
    }

    for (const DeliveryDriver* driver : drivers) {
        if (driver == nullptr) { continue; }

        driver->displayInfo();

        file << std::fixed << std::setprecision(2)
             << "Driver       : " << driver->getName()               << "\n"
             << "Vehicle      : " << driver->getVehicleType()        << "\n"
             << "Deliveries   : " << driver->getCompletedDeliveries() << "\n"
             << "Total Earned : " << driver->getTotalEarnings()       << " EGP\n"
             << "---\n";
    }

    file.close();
    std::cout << "Driver stats saved to driver_stats.txt\n";
}
