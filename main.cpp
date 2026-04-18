/*Anas Mohamed gamal 20246022
Ziad Gawad 20246055
group G6*/
#include <iostream>
#include "Customer.h"
#include "DeliveryDriver.h"

using namespace std;
// customers array
Customer** customers;
int customerCount = 0;
int customerCapacity = 10;

// drivers Array
DeliveryDriver** drivers;
int driverCount = 0;
int driverCapacity = 10;

//dynamic resizing
void resizeCustomers() {
    int newCapacity = customerCapacity * 2;
    Customer** newArr = new Customer*[newCapacity];
    for (int i=0; i<customerCount; i++) {
        newArr[i] = customers[i];
    }
    delete[] customers;
    customers = newArr;
    customerCapacity = newCapacity;
}

//dynamic resizing
void resizeDrivers() {
    int newCapacity = driverCapacity * 2;
    DeliveryDriver** newArr = new DeliveryDriver*[newCapacity];
    for (int i=0; i<driverCount; i++) {
        newArr[i] = drivers[i];
    }
    delete[] drivers;
    drivers = newArr;
    driverCapacity = newCapacity;
}

int main(){
    customers = new Customer*[customerCapacity];
    drivers = new DeliveryDriver*[driverCapacity];

int choice;
    do {
        cout << " ELMENUS MANAGEMENT SYSTEM v1.0 " << endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"         USER MANAGEMENT                      "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout << "1. Register New Customer" << endl;
        cout << "2. Register New Delivery Driver" << endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"         INFORMATION AND REPORTS              "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout << "3. Display Customer Info" << endl;
        cout << "4. Display Driver Info" << endl;
        cout<<"----------------------------------------------"<<endl;
        cout << "5. Exit System" << endl;
        cout << "Enter choice: ";
        cin>>choice;

        switch(choice) {
            case 1:  
            {
            if(customerCount==customerCapacity){
                resizeCustomers();
            }
            string id, n, ph, ad;
            cout << "enter customer ID: "; cin >> id;
            cout << "enter name: "; 
            cin.ignore();
            getline(cin, n);
            cout << "enter phone: ";
            getline(cin, ph);
            cout << "enter address: "; 
            getline(cin, ad);
            customers[customerCount++] = new Customer(id, n, ph, ad);
            cout<<"customer registered"<<endl;}
            break;

            case 2:
            {
            if(driverCount==driverCapacity){
                resizeDrivers();
            }
            string id, n, ph, v;
            cout << "enter driver ID: "; 
            cin >> id;
            cin.ignore();
            cout << "enter name: "; 
            getline(cin, n);
            cout << "enter phone: "; 
            getline(cin, ph);
            cout << "enter vehicle: "; 
            getline(cin, v);
            drivers[driverCount++] = new DeliveryDriver (id, n, ph, v,0,0.0);
            cout<<"driver registered"<<endl;}
            break;

            case 3:
            {
                //display info by customer id
                string custId;
                cout<<"enter customer ID "<<endl;
                cin>>custId;
                for(int i=0; i<customerCount; i++){
                    if(custId==customers[i]->getUserId()){
                        customers[i]->displayInfo();
                    }
                }
                break;
            }
            case 4:
            {
                //display info by driver id
                string driverId;
                cout<<"enter driver ID "<<endl;
                cin>>driverId;
                for(int i=0; i<driverCount; i++){
                    if(driverId==drivers[i]->getUserId()){
                        drivers[i]->displayInfo();
                    }
                }
                break;
            }

            case 5:
                cout<<"exiting"<<endl;
                break;

            default:
                cout<<"invalid choice"<<endl;
            
        }
    } while (choice != 5);
    for(int i=0; i<customerCount; i++) delete customers[i];
    delete[] customers;
    for(int i=0; i<driverCount; i++) delete drivers[i];
    delete[] drivers;
    return 0;
}