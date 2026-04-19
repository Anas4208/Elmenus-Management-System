#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "Customer.h"
#include "DeliveryDriver.h"

class ElmenusSystem {
private:
    std::vector<std::unique_ptr<Customer>> customers_;
    std::vector<std::unique_ptr<DeliveryDriver>> drivers_;
    
public:
    // Default constructor
    ElmenusSystem() = default;
    
    // Destructor - default is fine since we use smart pointers
    ~ElmenusSystem() = default;
    
    // Delete copy operations to prevent accidental copying (singleton-like behavior)
    ElmenusSystem(const ElmenusSystem&) = delete;
    ElmenusSystem& operator=(const ElmenusSystem&) = delete;
    
    // Allow move operations
    ElmenusSystem(ElmenusSystem&&) = default;
    ElmenusSystem& operator=(ElmenusSystem&&) = default;
    
    void displayMenu() const {
        std::cout << "\n========================================" << std::endl;
        std::cout << "    ELMENUS MANAGEMENT SYSTEM v2.0     " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "         USER MANAGEMENT                " << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "1. Register New Customer" << std::endl;
        std::cout << "2. Register New Delivery Driver" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "3. Display Customer Info" << std::endl;
        std::cout << "4. Display Driver Info" << std::endl;
        std::cout << "5. System Statistics" << std::endl;
        std::cout << "6. Exit System" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Enter choice: ";
    }
    
    void registerCustomer() {
        std::string id, name, phone, address;
        
        std::cout << "\n--- Customer Registration ---" << std::endl;
        std::cout << "Enter Customer ID: ";
        std::cin >> id;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Enter Name: ";
        std::getline(std::cin, name);
        
        std::cout << "Enter Phone: ";
        std::getline(std::cin, phone);
        
        std::cout << "Enter Address: ";
        std::getline(std::cin, address);
        
        customers_.push_back(std::make_unique<Customer>(id, name, phone, address));
        std::cout << "Customer registered successfully!" << std::endl;
    }
    
    void registerDriver() {
        std::string id, name, phone, vehicle;
        
        std::cout << "\n--- Driver Registration ---" << std::endl;
        std::cout << "Enter Driver ID: ";
        std::cin >> id;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Enter Name: ";
        std::getline(std::cin, name);
        
        std::cout << "Enter Phone: ";
        std::getline(std::cin, phone);
        
        std::cout << "Enter Vehicle Type: ";
        std::getline(std::cin, vehicle);
        
        drivers_.push_back(std::make_unique<DeliveryDriver>(id, name, phone, vehicle));
        std::cout << "Driver registered successfully!" << std::endl;
    }
    
    void displayCustomerInfo() const {
        if (customers_.empty()) {
            std::cout << "No customers registered yet." << std::endl;
            return;
        }
        
        std::string customerId;
        std::cout << "Enter Customer ID: ";
        std::cin >> customerId;
        
        for (const auto& customer : customers_) {
            if (customer->getUserId() == customerId) {
                customer->displayInfo();
                return;
            }
        }
        std::cout << "Customer not found!" << std::endl;
    }
    
    void displayDriverInfo() const {
        if (drivers_.empty()) {
            std::cout << "No drivers registered yet." << std::endl;
            return;
        }
        
        std::string driverId;
        std::cout << "Enter Driver ID: ";
        std::cin >> driverId;
        
        for (const auto& driver : drivers_) {
            if (driver->getUserId() == driverId) {
                driver->displayInfo();
                return;
            }
        }
        std::cout << "Driver not found!" << std::endl;
    }
    
    void displayStatistics() const {
        std::cout << "\n=== System Statistics ===" << std::endl;
        std::cout << "Total Customers: " << customers_.size() << std::endl;
        std::cout << "Total Drivers: " << drivers_.size() << std::endl;
        std::cout << "Total Users: " << User::getTotalUsers() << std::endl;
        std::cout << "=========================" << std::endl;
    }
    
    void run() {
        int choice = 0;
        
        while (choice != 6) {
            displayMenu();
            
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number." << std::endl;
                continue;
            }
            
            switch (choice) {
                case 1: registerCustomer(); break;
                case 2: registerDriver(); break;
                case 3: displayCustomerInfo(); break;
                case 4: displayDriverInfo(); break;
                case 5: displayStatistics(); break;
                case 6: std::cout << "\nThank you for using Elmenus System!" << std::endl; break;
                default: std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
};

int main() {
    try {
        ElmenusSystem system;
        system.run();
    } catch (const std::exception& e) {
        std::cerr << "System error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
