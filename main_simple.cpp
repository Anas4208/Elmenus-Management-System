#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Customer.h"
#include "DeliveryDriver.h"

using namespace std;

int main() {
    vector<Customer*> customers;
    vector<DeliveryDriver*> drivers;
    int choice = 0;
    
    while (choice != 6) {
        cout << "\n========================================" << endl;
        cout << "    ELMENUS MANAGEMENT SYSTEM v2.0     " << endl;
        cout << "========================================" << endl;
        cout << "1. Register New Customer" << endl;
        cout << "2. Register New Delivery Driver" << endl;
        cout << "3. Display Customer Info" << endl;
        cout << "4. Display Driver Info" << endl;
        cout << "5. Display System Statistics" << endl;
        cout << "6. Exit System" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                string id, name, phone, address;
                cout << "Enter Customer ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Phone: ";
                getline(cin, phone);
                cout << "Enter Address: ";
                getline(cin, address);
                customers.push_back(new Customer(id, name, phone, address));
                cout << "Customer registered!" << endl;
                break;
            }
            case 2: {
                string id, name, phone, vehicle;
                cout << "Enter Driver ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Phone: ";
                getline(cin, phone);
                cout << "Enter Vehicle: ";
                getline(cin, vehicle);
                drivers.push_back(new DeliveryDriver(id, name, phone, vehicle));
                cout << "Driver registered!" << endl;
                break;
            }
            case 3: {
                string custId;
                cout << "Enter Customer ID: ";
                cin >> custId;
                for (size_t i = 0; i < customers.size(); i++) {
                    if (customers[i]->getUserId() == custId) {
                        customers[i]->displayInfo();
                        break;
                    }
                }
                break;
            }
            case 4: {
                string driverId;
                cout << "Enter Driver ID: ";
                cin >> driverId;
                for (size_t i = 0; i < drivers.size(); i++) {
                    if (drivers[i]->getUserId() == driverId) {
                        drivers[i]->displayInfo();
                        break;
                    }
                }
                break;
            }
            case 5: {
                cout << "\n=== System Statistics ===" << endl;
                cout << "Total Customers: " << customers.size() << endl;
                cout << "Total Drivers: " << drivers.size() << endl;
                cout << "Total Users: " << User::getTotalUsers() << endl;
                break;
            }
            case 6:
                cout << "Exiting system..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    // Clean up memory
    for (size_t i = 0; i < customers.size(); i++) {
        delete customers[i];
    }
    for (size_t i = 0; i < drivers.size(); i++) {
        delete drivers[i];
    }
    
    return 0;
}
