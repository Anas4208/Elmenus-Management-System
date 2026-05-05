#include "FoodItem.h"

FoodItem::FoodItem() : itemName(""), price(0.0), quantity(0) {}

FoodItem::FoodItem(const std::string& name, double p, int q)
    : itemName(name), price(p), quantity(q) {}

std::string FoodItem::getItemName() const { return itemName; }
double      FoodItem::getPrice()    const { return price;    }
int         FoodItem::getQuantity() const { return quantity; }

void FoodItem::setItemName(const std::string& name) { itemName = name; }
void FoodItem::setPrice(double p)                   { price = p;       }
void FoodItem::setQuantity(int q)                   { quantity = q;    }

double FoodItem::calculateItemTotal() const {
    return price * static_cast<double>(quantity);
}

void FoodItem::displayItem() const {
    std::cout << std::fixed << std::setprecision(2)
              << itemName << " x" << quantity
              << " @ " << price << " EGP = "
              << calculateItemTotal() << " EGP\n";
}
