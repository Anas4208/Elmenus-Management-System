#ifndef DELIVERYDRIVER_H
#define DELIVERYDRIVER_H
#include "User.cpp"
#include <climits>

class DeliveryDriver :public User{
    private:
    string vehicleType;
    int completedDeliveries;
    double totalEarnings;
    public:
    DeliveryDriver();
    DeliveryDriver(string id, string n, string p, string v, int c, double t);
    void displayInfo();
    double calculateEarnings();
    void completeDelivery(double ordervalue);
    DeliveryDriver &operator++();
    DeliveryDriver operator++(int);
    int getCompletedDeliveries() const;
    double getTotalEarnings() const;
};
#endif

DeliveryDriver::DeliveryDriver(){
    vehicleType="";
    completedDeliveries=0;
    totalEarnings=0.0;
}
DeliveryDriver::DeliveryDriver(string id, string n, string p, string v, int c, double t): User(id, n, p){
    vehicleType=v;
    completedDeliveries=c;
    totalEarnings=t;
}
void DeliveryDriver::displayInfo(){
    cout<<"id: "<<userId<<endl;
    cout<<"name: "<<name<<endl;
    cout<<"phone: "<<phoneNumber<<endl;
    cout<<"completed deliveries: "<<completedDeliveries<<endl;
    cout<<"total earnings: "<<totalEarnings<<endl;
    if(completedDeliveries > 0){
        cout<<"average: "<<totalEarnings/completedDeliveries<<endl;
    }
}
double DeliveryDriver::calculateEarnings() { 
      return totalEarnings; }
void DeliveryDriver::completeDelivery(double ordervalue){
    if(ordervalue >= 0){
        totalEarnings += (0.15 * ordervalue);
    }
}
DeliveryDriver &DeliveryDriver::operator++(){
    if(completedDeliveries < INT_MAX){
        completedDeliveries++;
    }
    return *this;
} 
DeliveryDriver DeliveryDriver::operator++(int){
    DeliveryDriver temp = *this;
    if(completedDeliveries < INT_MAX){
        completedDeliveries++;
    }
    return temp;
}
int DeliveryDriver::getCompletedDeliveries() const { return completedDeliveries; }
double DeliveryDriver::getTotalEarnings() const { return totalEarnings; }
