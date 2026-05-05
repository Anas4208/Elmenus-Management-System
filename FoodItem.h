#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
#include <iostream>
#include <iomanip>

class FoodItem {
private:
    std::string itemName;
    double price;
    int quantity;

public:
    FoodItem();
    FoodItem(const std::string& name, double price, int quantity);

    std::string getItemName() const;
    double getPrice() const;
    int getQuantity() const;

    void setItemName(const std::string& name);
    void setPrice(double p);
    void setQuantity(int q);

    double calculateItemTotal() const;
    void displayItem() const;
};

#endif // FOODITEM_H
