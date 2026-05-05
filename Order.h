#ifndef ORDER_H
#define ORDER_H

#include "FoodItem.h"
#include "Customer.h"
#include "DeliveryDriver.h"
#include "Enums.h"
#include <ostream>

class Order {
private:
    std::string     orderId;
    Customer*       customer;
    DeliveryDriver* driver;
    FoodItem*       items;
    int             itemCount;
    int             capacity;
    OrderStatus     status;
    static int      totalOrders;

    void resize();

public:
    Order();
    Order(const std::string& oid, Customer* cust);
    Order(const Order& other);            // deep copy
    ~Order();

    // Disable assignment to avoid shallow-copy issues with raw pointer
    Order& operator=(const Order&) = delete;

    void addItem(const FoodItem& item);
    void assignDriver(DeliveryDriver* drv);
    void updateStatus(OrderStatus newStatus);

    double calculateTotal() const;
    void   displayOrder()   const;

    static int getTotalOrders();

    std::string     getOrderId()   const;
    Customer*       getCustomer()  const;
    DeliveryDriver* getDriver()    const;
    OrderStatus     getStatus()    const;
    int             getItemCount() const;

    Order& operator+=(const FoodItem& item);

    // Combine two orders into a new order (uses lhs customer)
    friend Order* combineOrders(const Order& lhs, const Order& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
    friend bool          operator>(const Order& lhs, const Order& rhs);

    FoodItem&       operator[](int index);
    const FoodItem& operator[](int index) const;
};

#endif // ORDER_H
