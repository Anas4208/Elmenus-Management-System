#include <iostream>
using namespace std;

void calculateDiscount1(double total) {
    double discount = 0;
    if (total > 1000) {
        discount = total * 0.15;
    } else if (total > 500) {
        discount = total * 0.10;
    } else if (total > 100) {
        discount = total * 0.05;
    }
    cout << "Discount: " << discount << endl;
}

void calculateDiscount2(double total) {
    double discount = 0;
    if (total > 1000) {
        discount = total * 0.15;
    } else if (total > 500) {
        discount = total * 0.10;
    } else if (total > 100) {
        discount = total * 0.05;
    }
    cout << "Discount: " << discount << endl;
}

void calculateDiscount3(double total) {
    double discount = 0;
    if (total > 1000) {
        discount = total * 0.15;
    } else if (total > 500) {
        discount = total * 0.10;
    } else if (total > 100) {
        discount = total * 0.05;
    }
    cout << "Discount: " << discount << endl;
}

int main() {
    calculateDiscount1(1000);
    calculateDiscount2(2000);
    calculateDiscount3(3000);
    return 0;
}
