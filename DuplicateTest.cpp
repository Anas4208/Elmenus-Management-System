#include <iostream>
#include <string>
using namespace std;

// This function will be duplicated below
void calculateCustomerDiscount1(double total) {
    double discount = 0;
    if (total > 1000) {
        discount = total * 0.15;
    } else if (total > 500) {
        discount = total * 0.10;
    } else if (total > 100) {
        discount = total * 0.05;
    } else {
        discount = 0;
    }
    cout << "Customer discount: " << discount << endl;
}

// DUPLICATE CODE STARTS HERE - Same logic, different name
void calculateCustomerDiscount2(double total) {
    double discount = 0;
    if (total > 1000) {
        discount = total * 0.15;
    } else if (total > 500) {
        discount = total * 0.10;
    } else if (total > 100) {
        discount = total * 0.05;
    } else {
        discount = 0;
    }
    cout << "Customer discount: " << discount << endl;
}

// Another duplicate - same logic again
void calculateCustomerDiscount3(double total) {
    double discount = 0;
    if (total > 1000) {
        discount = total * 0.15;
    } else if (total > 500) {
        discount = total * 0.10;
    } else if (total > 100) {
        discount = total * 0.05;
    } else {
        discount = 0;
    }
    cout << "Customer discount: " << discount << endl;
}

// Duplicate with minor changes (still detected)
void calculateDriverBonus(double earnings) {
    double bonus = 0;
    if (earnings > 1000) {
        bonus = earnings * 0.15;
    } else if (earnings > 500) {
        bonus = earnings * 0.10;
    } else if (earnings > 100) {
        bonus = earnings * 0.05;
    } else {
        bonus = 0;
    }
    cout << "Driver bonus: " << bonus << endl;
}

// Another duplicate block in a different function
void processOrder1() {
    string items[] = {"Pizza", "Burger", "Salad"};
    double prices[] = {50, 30, 20};
    int quantities[] = {2, 1, 3};
    
    double total = 0;
    for (int i = 0; i < 3; i++) {
        total += prices[i] * quantities[i];
        cout << items[i] << " x" << quantities[i] << " = " << prices[i] * quantities[i] << endl;
    }
    cout << "Total: " << total << endl;
}

// Duplicate of above
void processOrder2() {
    string items[] = {"Pizza", "Burger", "Salad"};
    double prices[] = {50, 30, 20};
    int quantities[] = {2, 1, 3};
    
    double total = 0;
    for (int i = 0; i < 3; i++) {
        total += prices[i] * quantities[i];
        cout << items[i] << " x" << quantities[i] << " = " << prices[i] * quantities[i] << endl;
    }
    cout << "Total: " << total << endl;
}

// Class with duplicate methods
class Calculator1 {
public:
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
    int multiply(int a, int b) { return a * b; }
    int divide(int a, int b) { return a / b; }
};

class Calculator2 {
public:
    int add(int a, int b) { return a + b; }
    int subtract(int a, int b) { return a - b; }
    int multiply(int a, int b) { return a * b; }
    int divide(int a, int b) { return a / b; }
};

int main() {
    calculateCustomerDiscount1(1000);
    calculateCustomerDiscount2(2000);
    calculateCustomerDiscount3(3000);
    calculateDriverBonus(1500);
    processOrder1();
    processOrder2();
    
    Calculator1 c1;
    Calculator2 c2;
    cout << "Add: " << c1.add(5, 3) << endl;
    cout << "Add: " << c2.add(5, 3) << endl;
    
    return 0;
}
