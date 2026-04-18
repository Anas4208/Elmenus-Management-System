/*Anas Mohamed gamal 20246022
Ziad Gawad 20246055
group G6*/
#include "DeliveryDriver.h"

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
    cout<<"average: "<<totalEarnings/completedDeliveries<<endl;
}
double DeliveryDriver::calculateEarnings() { 
      return totalEarnings; }
void DeliveryDriver::completeDelivery(double ordervalue){
    totalEarnings+=(0.15*ordervalue);
}
//prefix overload
DeliveryDriver &DeliveryDriver::operator++(){
    completedDeliveries++;
    return *this;
} 
//postfix overload dummy parameter
DeliveryDriver DeliveryDriver::operator++(int){
    DeliveryDriver temp=*this;
    completedDeliveries++;
    return temp;
}
int DeliveryDriver::getCompletedDeliveries() const { return completedDeliveries; }
double DeliveryDriver::getTotalEarnings() const { return totalEarnings; }