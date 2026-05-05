#include "Order.h"
#include "FileOps.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

// ── helpers ───────────────────────────────────────────────────────────────────
static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int readInt(const std::string& prompt) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            return value;
        }
        std::cout << "Invalid input. Please enter a whole number.\n";
        clearInput();
    }
}

static double readDouble(const std::string& prompt) {
    double value = 0.0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            return value;
        }
        std::cout << "Invalid input. Please enter a number.\n";
        clearInput();
    }
}

static std::string readString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// ── menu actions ──────────────────────────────────────────────────────────────
static void addCustomer(std::vector<Customer*>& customers) {
    std::string uid  = readString("Customer ID   : ");
    std::string name = readString("Name          : ");
    std::string phone = readString("Phone         : ");
    std::string addr  = readString("Address       : ");
    customers.push_back(new Customer(uid, name, phone, addr));
    std::cout << "Customer added.\n";
}

static void addDriver(std::vector<DeliveryDriver*>& drivers) {
    std::string uid     = readString("Driver ID     : ");
    std::string name    = readString("Name          : ");
    std::string phone   = readString("Phone         : ");
    std::string vehicle = readString("Vehicle type  : ");
    drivers.push_back(new DeliveryDriver(uid, name, phone, vehicle));
    std::cout << "Driver added.\n";
}

static void createOrder(std::vector<Order*>& orders,
                        const std::vector<Customer*>& customers) {
    if (customers.empty()) {
        std::cout << "No customers available. Add a customer first.\n";
        return;
    }
    std::cout << "Available customers:\n";
    for (int i = 0; i < static_cast<int>(customers.size()); ++i) {
        std::cout << "  " << i + 1 << ". " << customers[i]->getName() << "\n";
    }
    int choice = readInt("Select customer (number): ");
    if (choice < 1 || choice > static_cast<int>(customers.size())) {
        std::cout << "Invalid selection.\n";
        return;
    }
    std::string oid = readString("Order ID: ");
    orders.push_back(new Order(oid, customers[choice - 1]));
    std::cout << "Order created.\n";
}

static void addItemToOrder(std::vector<Order*>& orders) {
    if (orders.empty()) {
        std::cout << "No orders available.\n";
        return;
    }
    std::cout << "Available orders:\n";
    for (int i = 0; i < static_cast<int>(orders.size()); ++i) {
        std::cout << "  " << i + 1 << ". Order " << orders[i]->getOrderId() << "\n";
    }
    int choice = readInt("Select order (number): ");
    if (choice < 1 || choice > static_cast<int>(orders.size())) {
        std::cout << "Invalid selection.\n";
        return;
    }
    std::string itemName = readString("Item name : ");
    double price  = readDouble("Price     : ");
    int    qty    = readInt   ("Quantity  : ");
    if (price <= 0.0 || qty <= 0) {
        std::cout << "Price and quantity must be positive.\n";
        return;
    }
    *orders[choice - 1] += FoodItem(itemName, price, qty);
    std::cout << "Item added.\n";
}

static void assignDriverToOrder(std::vector<Order*>& orders,
                                const std::vector<DeliveryDriver*>& drivers) {
    if (orders.empty() || drivers.empty()) {
        std::cout << "Need at least one order and one driver.\n";
        return;
    }
    std::cout << "Orders:\n";
    for (int i = 0; i < static_cast<int>(orders.size()); ++i) {
        std::cout << "  " << i + 1 << ". " << orders[i]->getOrderId() << "\n";
    }
    int oc = readInt("Select order: ");
    if (oc < 1 || oc > static_cast<int>(orders.size())) {
        std::cout << "Invalid.\n"; return;
    }
    std::cout << "Drivers:\n";
    for (int i = 0; i < static_cast<int>(drivers.size()); ++i) {
        std::cout << "  " << i + 1 << ". " << drivers[i]->getName() << "\n";
    }
    int dc = readInt("Select driver: ");
    if (dc < 1 || dc > static_cast<int>(drivers.size())) {
        std::cout << "Invalid.\n"; return;
    }
    orders[oc - 1]->assignDriver(drivers[dc - 1]);
    std::cout << "Driver assigned.\n";
}

static void updateOrderStatus(std::vector<Order*>& orders) {
    if (orders.empty()) {
        std::cout << "No orders.\n"; return;
    }
    std::cout << "Orders:\n";
    for (int i = 0; i < static_cast<int>(orders.size()); ++i) {
        std::cout << "  " << i + 1 << ". " << orders[i]->getOrderId() << "\n";
    }
    int oc = readInt("Select order: ");
    if (oc < 1 || oc > static_cast<int>(orders.size())) {
        std::cout << "Invalid.\n"; return;
    }
    std::cout << "Status options:\n"
              << "  1. PENDING\n  2. PREPARING\n"
              << "  3. OUT_FOR_DELIVERY\n  4. DELIVERED\n  5. CANCELLED\n";
    int sc = readInt("Select status: ");
    OrderStatus newStatus;
    switch (sc) {
        case 1: newStatus = OrderStatus::PENDING;          break;
        case 2: newStatus = OrderStatus::PREPARING;        break;
        case 3: newStatus = OrderStatus::OUT_FOR_DELIVERY; break;
        case 4: newStatus = OrderStatus::DELIVERED;        break;
        case 5: newStatus = OrderStatus::CANCELLED;        break;
        default:
            std::cout << "Invalid status.\n";
            return;
    }
    orders[oc - 1]->updateStatus(newStatus);
    std::cout << "Status updated.\n";
}

static void displayAllOrders(const std::vector<Order*>& orders) {
    if (orders.empty()) {
        std::cout << "No orders.\n"; return;
    }
    for (const Order* o : orders) {
        std::cout << *o;
    }
}

static void displayAllCustomers(const std::vector<Customer*>& customers) {
    if (customers.empty()) {
        std::cout << "No customers.\n"; return;
    }
    for (const Customer* c : customers) { c->displayInfo(); }
}

static void displayAllDrivers(const std::vector<DeliveryDriver*>& drivers) {
    if (drivers.empty()) {
        std::cout << "No drivers.\n"; return;
    }
    for (const DeliveryDriver* d : drivers) { d->displayInfo(); }
}

static void compareOrders(const std::vector<Order*>& orders) {
    if (orders.size() < 2) {
        std::cout << "Need at least 2 orders to compare.\n"; return;
    }
    std::cout << "Select first order:\n";
    for (int i = 0; i < static_cast<int>(orders.size()); ++i) {
        std::cout << "  " << i + 1 << ". " << orders[i]->getOrderId() << "\n";
    }
    int a = readInt("First: ");
    int b = readInt("Second: ");
    if (a < 1 || a > static_cast<int>(orders.size()) ||
        b < 1 || b > static_cast<int>(orders.size())) {
        std::cout << "Invalid selection.\n"; return;
    }
    if (*orders[a - 1] > *orders[b - 1]) {
        std::cout << orders[a - 1]->getOrderId()
                  << " has a higher total.\n";
    } else {
        std::cout << orders[b - 1]->getOrderId()
                  << " has a higher or equal total.\n";
    }
}


// ── main ──────────────────────────────────────────────────────────────────────
int main() {
    std::vector<Customer*>       customers;
    std::vector<DeliveryDriver*> drivers;
    std::vector<Order*>          orders;

    bool running = true;
    while (running) {
        std::cout << "\n======== EIMenus Order Management ========\n"
                  << " 1.  Add Customer\n"
                  << " 2.  Add Driver\n"
                  << " 3.  Create Order\n"
                  << " 4.  Add Item to Order\n"
                  << " 5.  Assign Driver to Order\n"
                  << " 6.  Update Order Status\n"
                  << " 7.  Display All Orders\n"
                  << " 8.  Display All Customers\n"
                  << " 9.  Display All Drivers\n"
                  << "10.  Compare Two Orders\n"
                  << "11.  Save Completed Orders to File\n"
                  << "12.  Save Driver Stats to File\n"
                  << "13.  Show System Stats\n"
                  << " 0.  Exit\n"
                  << "==========================================\n";

        int choice = readInt("Choice: ");
        switch (choice) {
            case 1:  addCustomer(customers);                         break;
            case 2:  addDriver(drivers);                             break;
            case 3:  createOrder(orders, customers);                 break;
            case 4:  addItemToOrder(orders);                         break;
            case 5:  assignDriverToOrder(orders, drivers);           break;
            case 6:  updateOrderStatus(orders);                      break;
            case 7:  displayAllOrders(orders);                       break;
            case 8:  displayAllCustomers(customers);                 break;
            case 9:  displayAllDrivers(drivers);                     break;
            case 10: compareOrders(orders);                          break;
            case 11: saveCompletedOrders(orders);                    break;
            case 12: saveDriverStats(drivers);                       break;
            case 13:
                std::cout << "Total Users  : " << User::getTotalUsers()   << "\n"
                          << "Total Orders : " << Order::getTotalOrders() << "\n";
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Invalid option. Please enter 0-13.\n";
        }
    }


    std::cout << "Goodbye!\n";
    return 0;
}
