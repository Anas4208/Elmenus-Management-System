#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include "Customer.cpp"
#include "DeliveryDriver.cpp"
#include "FoodItem.cpp"
#include "Enums.h"
using namespace std;

class Order {
    private:
    string orderId;
    Customer* customer;
    DeliveryDriver* driver;
    FoodItem* items;
    int itemCount;
    int capacity;
    OrderStatus status;
    static int totalOrders;
    public:
    Order();
    Order(string id, Customer *ptr);
    Order(const Order & obj);
    ~Order();
    void addItem(const FoodItem &item);
    void assignDriver(DeliveryDriver* drv);
    double calculateTotal() const;
    void updateStatus(OrderStatus newStatus);
    void displayOrder()const;
    //geters
    static int getTotalOrders();
    int getItemCount();
    string getOrderId() const;
    OrderStatus getStatus() const;
    Customer* getCustomer() const;
    DeliveryDriver* getDriver() const;
    
    Order &operator+=(const FoodItem & obj);
    Order operator+(const Order & obj);
    //output operator displays all order details
    friend ostream &operator<<(ostream& os,const Order &obj);
    //greater than operator
    friend bool operator>(const Order &obj,const Order&obj2);
    FoodItem &operator[]( int i);
};
#endif

int Order::totalOrders = 0;
//default constructor
Order::Order(){
    orderId="";
    customer=0;
    driver=0;
    items=0;
    itemCount=0;
    capacity=10;
    status=OrderStatus::PENDING;
    items = new FoodItem[capacity];
    totalOrders++;
}
//parameterized constructor
Order::Order(string id, Customer *ptr){
    orderId=id;
    customer=ptr;
    driver=0;
    items=0;
    itemCount=0;
    capacity=1;
    status=OrderStatus::PENDING;
    items = new FoodItem[capacity];
    totalOrders++; 
}
//copy constructor
Order::Order(const Order & obj){
    orderId=obj.orderId;
    customer=obj.customer;
    driver=obj.driver;
    itemCount=obj.itemCount;
    capacity=obj.capacity;
    status=obj.status;
    items = new FoodItem[capacity];
    for(int i = 0; i < itemCount; i++) {
        items[i] = obj.items[i];
    }
}
//destructor
Order::~Order() {
    delete[] items;
}
void Order::addItem(const FoodItem &item){
    //dynamic resizing if item count is equal to the capacity then must increase capacity
    if(itemCount==capacity){
        capacity*=2;
        //create new array on new capacity
        FoodItem* newItems=new FoodItem[capacity];
        //copy array
        for(int i=0;i<itemCount;i++){
            newItems[i]=items[i];
        }
        delete[] items;
        items = newItems;
    }
    items[itemCount++] = item;
}
void Order::assignDriver(DeliveryDriver* drv) {
    driver = drv;
}
double Order::calculateTotal() const {
    double total = 0;
    for(int i=0; i<itemCount; i++) {
        total += items[i].calculateItemTotal();
    }
    return total;
}
void Order::updateStatus(OrderStatus newStatus){
    status=newStatus;
    if(newStatus==OrderStatus::DELIVERED){
        double total=calculateTotal();

        driver->completeDelivery(total);
        (*driver)++;
        //add loyalty points
        *customer += static_cast<int>(total)/2;
    }

}
void Order::displayOrder()const{
    //make an array with string values of enums to use in output
    string statusLabels[] = {"PENDING", "PREPARING", "OUT_FOR_DELIVERY", "DELIVERED", "CANCELLED"};
    cout<< "order ID: "<< orderId<<endl;
    cout<< "status: "<<statusLabels[(int)status]<< endl;
    cout<< "customer: "<< customer->getName() << endl;
    cout<< "driver: " << driver->getName() << endl;
    cout<< "items" << endl;
    for(int i=0; i<itemCount; i++) {
        items[i].displayItem();
    }
    cout << "total amount:"<<calculateTotal() << endl;
}
//geters
int Order::getTotalOrders() { 
    return totalOrders; }
int Order::getItemCount(){
    return itemCount;
}
string Order::getOrderId() const {
    return orderId; }
OrderStatus Order::getStatus() const { 
    return status; }
Customer* Order::getCustomer() const { 
    return customer; }
DeliveryDriver* Order::getDriver() const {
     return driver; }

Order &Order::operator+=(const FoodItem & obj){
    addItem(obj);
    return *this;
}
Order Order::operator+(const Order & obj){
    Order newOrder(this->orderId +"-"+ obj.orderId, this->customer);
    for(int i = 0; i < this->itemCount; i++) {
        newOrder.addItem(this->items[i]);}
    for(int i = 0; i < obj.itemCount; i++) {
        newOrder.addItem(obj.items[i]);}
    return newOrder;

}
//output operator displays all order details
ostream &operator<<(ostream& os,const Order &obj){
    string statusLabels[] = {"PENDING", "PREPARING", "OUT_FOR_DELIVERY", "DELIVERED", "CANCELLED"};
    os<< "status: "<<statusLabels[(int)obj.status]<< endl;
    os << "order ID: " << obj.orderId <<endl;
    os << "customer: " << obj.customer->getName() << endl;
    os << "driver: " << obj.driver->getName() << endl;
    os << "items" << endl;
    //prints item details for each item
    for(int i = 0; i < obj.itemCount; i++) {
        os << obj.items[i].getItemName()<<endl;
        os <<"quantity: " <<obj.items[i].getQuantity()<<endl;
        os<< "price : " << obj.items[i].calculateItemTotal() << endl;
    } 
    os << "total amount: " << obj.calculateTotal() << endl;
    return os;


}
//greater than operator
bool operator>(const Order &obj,const Order&obj2){
    if(obj.calculateTotal()>obj2.calculateTotal()){
        return true;
    }
    return false;

}
FoodItem &Order::operator[]( int i){
    return items[i];

}