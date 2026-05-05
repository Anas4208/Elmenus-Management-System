#include "Order.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

int Order::totalOrders = 0;

// ── private helper ────────────────────────────────────────────────────────────
void Order::resize() {
    int newCap = capacity * 2;
    FoodItem* newItems = new FoodItem[newCap];
    for (int i = 0; i < itemCount; ++i) {
        newItems[i] = items[i];
    }
    delete[] items;
    items    = newItems;
    capacity = newCap;
}

// ── constructors / destructor ─────────────────────────────────────────────────
Order::Order()
    : orderId(""), customer(nullptr), driver(nullptr),
      items(new FoodItem[4]), itemCount(0), capacity(4),
      status(OrderStatus::PENDING) {
    ++totalOrders;
}

Order::Order(const std::string& oid, Customer* cust)
    : orderId(oid), customer(cust), driver(nullptr),
      items(new FoodItem[4]), itemCount(0), capacity(4),
      status(OrderStatus::PENDING) {
    ++totalOrders;
}

Order::Order(const Order& other)
    : orderId(other.orderId), customer(other.customer), driver(other.driver),
      items(new FoodItem[other.capacity]), itemCount(other.itemCount),
      capacity(other.capacity), status(other.status) {
    for (int i = 0; i < itemCount; ++i) {
        items[i] = other.items[i];
    }
    ++totalOrders;
}

Order::~Order() {
    delete[] items;
    --totalOrders;
}

// ── methods ───────────────────────────────────────────────────────────────────
void Order::addItem(const FoodItem& item) {
    if (itemCount == capacity) {
        resize();
    }
    items[itemCount++] = item;
}

void Order::assignDriver(DeliveryDriver* drv) {
    driver = drv;
}

void Order::updateStatus(OrderStatus newStatus) {
    status = newStatus;
    if (newStatus == OrderStatus::DELIVERED) {
        double total = calculateTotal();
        if (driver != nullptr) {
            driver->completeDelivery(total);
            ++(*driver);
        }
        if (customer != nullptr) {
            int pts = static_cast<int>(total / 10);
            *customer += pts;
        }
    }
}

double Order::calculateTotal() const {
    double total = 0.0;
    for (int i = 0; i < itemCount; ++i) {
        total += items[i].calculateItemTotal();
    }
    return total;
}

void Order::displayOrder() const {
    std::cout << *this;
}

int Order::getTotalOrders() { return totalOrders; }

std::string     Order::getOrderId()   const { return orderId;   }
Customer*       Order::getCustomer()  const { return customer;  }
DeliveryDriver* Order::getDriver()    const { return driver;    }
OrderStatus     Order::getStatus()    const { return status;    }
int             Order::getItemCount() const { return itemCount; }

// ── operators ─────────────────────────────────────────────────────────────────
Order& Order::operator+=(const FoodItem& item) {
    addItem(item);
    return *this;
}

FoodItem& Order::operator[](int index) {
    if (index < 0 || index >= itemCount) {
        throw std::out_of_range("Order index out of range");
    }
    return items[index];
}

const FoodItem& Order::operator[](int index) const {
    if (index < 0 || index >= itemCount) {
        throw std::out_of_range("Order index out of range");
    }
    return items[index];
}

// ── friends ───────────────────────────────────────────────────────────────────
Order* combineOrders(const Order& lhs, const Order& rhs) {
    Order* combined = new Order(lhs.orderId + "_" + rhs.orderId, lhs.customer);
    combined->driver = lhs.driver;
    combined->status = lhs.status;
    for (int i = 0; i < lhs.itemCount; ++i) {
        combined->addItem(lhs.items[i]);
    }
    for (int i = 0; i < rhs.itemCount; ++i) {
        combined->addItem(rhs.items[i]);
    }
    return combined;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << std::fixed << std::setprecision(2)
       << "==================== ORDER ====================\n"
       << "Order ID : " << order.orderId << "\n";

    if (order.customer != nullptr) {
        os << "Customer : " << order.customer->getName() << "\n"
           << "Address  : " << order.customer->getDeliveryAddress() << "\n";
    }
    if (order.driver != nullptr) {
        os << "Driver   : " << order.driver->getName() << "\n";
    }

    os << "Items    :\n";
    for (int i = 0; i < order.itemCount; ++i) {
        os << "  ";
        order.items[i].displayItem();
    }
    os << "Total    : " << order.calculateTotal() << " EGP\n"
       << "===============================================\n";
    return os;
}

bool operator>(const Order& lhs, const Order& rhs) {
    return lhs.calculateTotal() > rhs.calculateTotal();
}
