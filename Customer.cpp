/*Anas Mohamed gamal 20246022
Ziad Gawad 20246055
group G6*/
#include "Customer.h"
//default constructor
Customer::Customer(){
    deliveryAddress="";
    loyaltyPoints=0;
}
//parameterized construtor
Customer::Customer(string id, string n, string p, string a):User(id, n, p){
    deliveryAddress=a;
    loyaltyPoints=0;
}
void Customer::displayInfo(){
    cout<<"id: "<<userId<<endl;
    cout<<"name: "<<name<<endl;
    cout<<"phone: "<<phoneNumber<<endl;
    cout<<"address: "<<deliveryAddress<<endl;
    cout<<"loyalty points: "<<loyaltyPoints<<endl;
}
double Customer::calculateEarnings(){
    return loyaltyPoints*0.5;
}
void Customer::setLoyaltyPoints(int p) { 
    loyaltyPoints = p; }
int Customer::getLoyaltyPoints() const { return loyaltyPoints; }
Customer &Customer::operator+=(int p){
    this->loyaltyPoints+=p;
    return *this;

}