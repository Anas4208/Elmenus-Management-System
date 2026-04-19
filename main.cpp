#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "Customer.h"
#include "DeliveryDriver.h"

class UserManagementSystem {
private:
    std::vector<Customer*> customers_;
    std::vector<DeliveryDriver*> drivers_;
    
    void displayMainMenu() const {
        std::cout << "\n========================================" << std::endl;
        std::cout << "    ELMENUS MANAGEMENT SYSTEM v2.0     " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "         USER MANAGEMENT                " << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "1. Register New Customer" << std::endl;
        std::cout << "2. Register New Delivery Driver" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "         INFORMATION AND REPORTS        " << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "3. Display Customer Info" << std::endl;
        std::cout << "4. Display Driver Info" << std::endl;
        std::cout << "5. Display System Statistics" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "6. Exit System" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Enter choice: ";
    }
    
    void registerCustomer() {
        std::string id, name, phone, address;
        
        std::cout << "\n--- New Customer Registration ---" << std::endl;
        std::cout << "Enter Customer ID: ";
        std::cin >> id;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Enter Name: ";
        std::getline(std::cin, name);
        
        std::cout << "Enter Phone: ";
        std::getline(std::cin, phone);
        
        std::cout << "Enter Delivery Address: ";
        std::getline(std::cin, address);
        
        customers_.push_back(new Customer(id, name, phone, address));
        std::cout << "✓ Customer registered successfully!" << std::endl;
    }
    
    void registerDriver() {
        std::string id, name, phone, vehicle;
        
        std::cout << "\n--- New Driver Registration ---" << std::endl;
        std::cout << "Enter Driver ID: ";
        std::cin >> id;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Enter Name: ";
        std::getline(std::cin, name);
        
        std::cout << "Enter Phone: ";
        std::getline(std::cin, phone);
        
        std::cout << "Enter Vehicle Type: ";
        std::getline(std::cin, vehicle);
        
        drivers_.push_back(new DeliveryDriver(id, name, phone, vehicle));
        std::cout << "✓ Driver registered successfully!" << std::endl;
    }
    
    void displayCustomerInfo() const {
        if (customers_.empty()) {
            std::cout << "No customers registered yet." << std::endl;
            return;
        }
        
        std::string customerId;
        std::cout << "Enter Customer ID: ";
        std::cin >> customerId;
        
        bool found = false;
        for (size_t i = 0; i < customers_.size(); ++i) {
            if (customers_[i]->getUserId() == customerId) {
                customers_[i]->displayInfo();
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::cout << "Customer not found!" << std::endl;
        }
    }
    
    void displayDriverInfo() const {
        if (drivers_.empty()) {
            std::cout << "No drivers registered yet." << std::endl;
            return;
        }
        
        std::string driverId;
        std::cout << "Enter Driver ID: ";
        std::cin >> driverId;
        
        bool found = false;
        for (size_t i = 0; i < drivers_.size(); ++i) {
            if (drivers_[i]->getUserId() == driverId) {
                drivers_[i]->displayInfo();
                found = true;
                break;
            }
        }
        
        if (!found) {
            std::cout << "Driver not found!" << std::endl;
        }
    }
    
    void displayStatistics() const {
        std::cout << "\n=== System Statistics ===" << std::endl;
        std::cout << "Total Users: " << User::getTotalUsers() << std::endl;
        std::cout << "Total Customers: " << customers_.size() << std::endl;
        std::cout << "Total Drivers: " << drivers_.size() << std::endl;
        
        double totalEarnings = 0.0;
        for (size_t i = 0; i < drivers_.size(); ++i) {
            totalEarnings += drivers_[i]->getTotalEarnings();
        }
        std::cout << "Total Driver Earnings: $" << totalEarnings << std::endl;
        std::cout << "=========================" << std::endl;
    }
    
public:
    UserManagementSystem() {
        // Constructor
    }
    
    ~UserManagementSystem() {
        // Clean up memory
        for (size_t i = 0; i < customers_.size(); ++i) {
            delete customers_[i];
        }
        for (size_t i = 0; i < drivers_.size(); ++i) {
            delete drivers_[i];
        }
    }
    
    void run() {
        int choice = 0;
        
        while (choice != 6) {
            displayMainMenu();
            
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number." << std::endl;
                continue;
            }
            
            switch (choice) {
                case 1:
                    registerCustomer();
                    break;
                case 2:
                    registerDriver();
                    break;
                case 3:
                    displayCustomerInfo();
                    break;
                case 4:
                    displayDriverInfo();
                    break;
                case 5:
                    displayStatistics();
                    break;
                case 6:
                    std::cout << "\nThank you for using Elmenus Management System!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
            }
        }
    }
};

int main() {
    try {
        UserManagementSystem system;
        system.run();
    } catch (const std::exception& e) {
        std::cerr << "System error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}