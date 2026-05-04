#ifndef FOODITEM_H
#define FOODITEM_H
#include <iostream>
#include<iomanip>
using namespace std;

class FoodItem {
    private:
    string itemName;
    double price;
    int quantity;
    public:
    //default constructor
    FoodItem();
    //parameterized constructor
    FoodItem(string i, double p, int q);
    //setters and getters
    void setItemName(string i);
    void setPrice(double p);
    void setQuantity(int q);
    string getItemName() const;
    double getPrice() const;
    int getQuantity() const;
    //calculate total
    double calculateItemTotal() const;
    void displayItem() const;
};
#endif

//default constructor
FoodItem::FoodItem(){
    itemName="";
    price=0.0;
    quantity=0;
}
//parameterized constructor
FoodItem::FoodItem(string i, double p, int q){
    itemName=i;
    price=p;
    quantity=q;
}
//setters and getters
void FoodItem::setItemName(string i){
    itemName=i;}
void FoodItem::setPrice(double p){
    price=p;}
void FoodItem::setQuantity(int q){quantity=q;}
string FoodItem::getItemName() const { return itemName; }
double FoodItem::getPrice() const { return price; }
int FoodItem::getQuantity() const { return quantity; }
//calculate total
double FoodItem::calculateItemTotal() const{
    return price*quantity;
}
void FoodItem::displayItem() const {
    cout << itemName << " x" << quantity << " @ " << fixed << setprecision(2) << price << " EGP = " << calculateItemTotal() << " EGP" << endl;
}