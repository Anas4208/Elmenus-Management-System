#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "User.cpp" 

class Customer :public User {
    private:
    string deliveryAddress;
    int loyaltyPoints;
    public:
    Customer();
    Customer(string id, string n, string p, string a);
    void displayInfo();
    double calculateEarnings();
    void setLoyaltyPoints(int p);
    int getLoyaltyPoints() const;
    Customer &operator+=(int p);
};
#endif

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