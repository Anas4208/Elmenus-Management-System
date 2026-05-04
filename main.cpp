/*Anas Mohamed gamal 20246022
Ziad Gawad 20246055
group G6*/
#include <iostream>
#include <fstream>
#include <chrono>
#include <iostream>
#include <cstring>
#include "FoodItem.h"
#include "Customer.h"
#include "DeliveryDriver.h"
#include "Order.h"

using namespace std;
// customers array
Customer** customers;
int customerCount = 0;
int customerCapacity = 10;

// drivers Array
DeliveryDriver** drivers;
int driverCount = 0;
int driverCapacity = 10;

// orders Array
Order** orders;
int orderCount = 0;
int orderCapacity = 10;

void saveOrders( Order *orders[],int count) {
    ofstream outFile("completed_orders.txt");  
    if(outFile) {
        for(int i=0;i<count;i++) {
            if(orders[i]->getStatus() == OrderStatus::DELIVERED) {
                outFile << "ID: " << orders[i]->getOrderId()<< " total: " << orders[i]->calculateTotal() << endl;
                cout << "saved order" << orders[i]->getOrderId() << endl;
            }
        }
        outFile.close();
    } else {
        cout << "error opening file" << endl;
    }
}
void saveDriver( DeliveryDriver *drivers[],int count){
    ofstream outfile("driver_stats.txt");
    //check if file is open
    if(outfile){
        for(int i=0;i<count;i++){
            //copy to file
            outfile<<"total earnings "<<drivers[i]->getTotalEarnings()<<"total deliveries "<<drivers[i]->getCompletedDeliveries()<<endl;
        }
        outfile.close();
    } else {
        cout << "error opening file" << endl;
    }

}
struct Item {
    char name[50];
    double price;
    int quantity;
};

struct OrderRecord {
    char orderId[20];
    char customerName[50];
    char driverName[50];
    double totalAmount;
    int status;
    int itemCount;
    Item items[10];

};


void saveOrdersToBinary() {
    ofstream outFile("orders.dat", ios::binary | ios::out);
    if (!outFile) {
        cout << "error opening file" << endl;
        return;
    }

    int savedCount = 0;
    for (int i=0; i<orderCount; i++) {
        OrderRecord record;
        Order* currentOrder = orders[i];
        
        // copy string data into fixed-size char arrays
        strncpy(record.orderId, currentOrder->getOrderId().c_str(), sizeof(record.orderId) - 1);
        strncpy(record.customerName, currentOrder->getCustomer()->getName().c_str(), sizeof(record.customerName) - 1);
        strncpy(record.driverName, currentOrder->getDriver()->getName().c_str(), sizeof(record.driverName) - 1);
        record.totalAmount = currentOrder->calculateTotal();
        record.status = (int)currentOrder->getStatus();
        
        // copy items (up to 10)
        record.itemCount = 0;
        int currentItems = currentOrder->getItemCount();
        
        // access items   
        for (int j=0; j<currentItems && j<10; j++) {
            FoodItem& item = (*currentOrder)[j];
            strncpy(record.items[j].name, item.getItemName().c_str(), 49);
            record.items[j].price = item.getPrice();
            record.items[j].quantity = item.getQuantity();
            record.itemCount++;
        }

        // write the struct to file
        outFile.write(reinterpret_cast<char*>(&record), sizeof(OrderRecord));
        savedCount++;
    }
    
    
    outFile.close();
    cout << "successfully saved " << savedCount << " orders" << endl;
}

void loadOrderFromBinary(int num) {
    ifstream inFile("orders.dat", ios::binary);
    if (!inFile) {
        cout << "error could not open file" << endl;
        return;
    }

    // check total records to validate index
    inFile.seekg(0, ios::end);
    long fileSize = inFile.tellg();
    int totalRecords = fileSize / sizeof(OrderRecord);

    if (num <1 || num > totalRecords) {
        cout << "error index, total records: " << totalRecords << endl;
        return;
    }

    // start timer
    auto start = chrono::high_resolution_clock::now();

    // jump directly to the specific record
    int pos = (num-1) * sizeof(OrderRecord);
    inFile.seekg(pos, ios::beg);
    // read to file to desired position
    OrderRecord record;
    inFile.read(reinterpret_cast<char*>(&record), sizeof(OrderRecord));

    // end timer
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, nano> elapsed = end - start;

    inFile.close();
    // display Record
    cout << "time taken: " << elapsed.count()<< endl;
    cout << "order ID: " << record.orderId << endl;
    cout << "customer: " << record.customerName << endl;
    cout << "driver:   " << record.driverName << endl;
    cout << "items:" << endl;
    for(int i=0; i<record.itemCount; i++) {
         cout<< record.items[i].name << " (" << record.items[i].quantity << ")" << endl;
    }
    cout << "total: " << record.totalAmount << " EGP" << endl;
}
void showBinaryFileStats() {
    //open file
    ifstream inFile("orders.dat", ios::binary );
    if (!inFile) {
        cout << "no file found." << endl;
        return;
    }
    long size = inFile.tellg();
    cout << "file Size: " << size << endl;
    cout << "record Size: " << sizeof(OrderRecord) << endl;
    cout << "total Records: " << size / sizeof(OrderRecord) << endl;
    inFile.close();
}


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

//dynamic resizing
void resizeOrders() {
    int newCapacity = orderCapacity * 2;
    Order** newArr = new Order*[newCapacity];
    for (int i=0; i<orderCount; i++) {
        newArr[i] = orders[i];
    }
    delete[] orders;
    orders = newArr;
    orderCapacity = newCapacity;
}
int main(){
    customers = new Customer*[customerCapacity];
    drivers = new DeliveryDriver*[driverCapacity];
    orders = new Order*[orderCapacity];

int choice;
    do {
        cout << " ELMENUS MANAGEMENT SYSTEM v1.0 " << endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"         USER MANAGEMENT                      "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout << "1. Register New Customer" << endl;
        cout << "2. Register New Delivery Driver" << endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"         ORDER MANAGEMENT                     "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout << "3. Create New Order" << endl;
        cout << "4. Add Items to Order" << endl;
        cout << "5. Assign Driver to Order" << endl;
        cout << "6. Update Order Status" << endl;
        cout << "7. Display Order Details" << endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"         INFORMATION AND REPORTS              "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout << "8. Display Customer Info" << endl;
        cout << "9. Display Driver Info" << endl;
        cout << "10. Compare Two Orders by Total" << endl;
        cout << "11. Display System Statistics" << endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"        FILE OPERATIONS                       "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout << "12. Save Completed Orders to File" << endl;
        cout << "13. Save Driver Stats to File" << endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"        BONUS FEATURES                        "<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout << "14. Save Orders to Binary File" << endl;
        cout << "15. Load Order by Position (O(1))" << endl;
        cout << "16. Binary File Statistics" << endl;
        cout<<"----------------------------------------------"<<endl;
        cout << "17. Exit System" << endl;
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
            //validate that there is customers
            if (customerCount == 0) { cout << "Register a customer first." << endl; 
                break; }
            if (orderCount == orderCapacity) {
                resizeOrders();}
            string orderId, custId;
            cout<<"enter order ID: "<<endl;
            cin>>orderId;
            cout<<"enter customer ID: "<<endl;
            cin>>custId;
            Customer *thisCustomer=nullptr;
            //search for the customer
            for(int i=0; i<customerCount; i++){
                if(custId==customers[i]->getUserId()){
                    thisCustomer=customers[i]; 
                    break;
                }

            }
            if(thisCustomer){
                orders[orderCount++] = new Order(orderId, thisCustomer);
                cout<<"order created sucsessfully"<<endl;
            }else {
                cout<<"customer not found"<<endl;
            }
            }
            break;

            case 4:
            {
                if(orderCount==0){
                    cout<<"no orders"<<endl;
                    break;
                }
                string orderId;
                Order *thisOrder=nullptr;
                cout<<"enter order ID: "<<endl;
                cin>>orderId;
                //search for the order
                for(int i=0; i<orderCount; i++){
                    if(orderId==orders[i]->getOrderId()){
                        thisOrder=orders[i];
                        break;
                    }
                }
            string n; double p; int qty;
            cin.ignore();
            cout << "enter item name: "; 
            getline(cin, n);
            cout << "enter price: "; 
            cin >> p;
            cout << "enter quantity: "; 
            cin >> qty;
            
            FoodItem item(n, p, qty);
            thisOrder->addItem(item);
            cout << "item added" << endl;

            }
            break;
            
            case 5:
            {
                //validate that there is drivers
                if(driverCount==0){
                    cout<<"no drivers"<<endl;
                    break;
                }
                string orderId;
                Order *thisOrder=nullptr;
                cout<<"enter order ID: "<<endl;
                cin>>orderId;
                //search for the order
                for(int i=0; i<orderCount; i++){
                    if(orderId==orders[i]->getOrderId()){
                        thisOrder=orders[i];
                    }
                }
                //makes sure order exists
                if(thisOrder){
                    string driverId;
                    cout << "enter driver ID: "; 
                    cin >> driverId;
                    DeliveryDriver* selectedDriver = nullptr;
                    for (int i = 0; i < driverCount; i++) {
                        if (drivers[i]->getUserId() == driverId) { 
                            selectedDriver = drivers[i];
                            break; 
                            }
                    }
                    //if user id matches driver id assign driver and update status
                    if (selectedDriver) {
                        thisOrder->assignDriver(selectedDriver);
                        thisOrder->updateStatus(OrderStatus::OUT_FOR_DELIVERY);
                        cout << "driver assigned " << endl;
                    } else {
                        cout << "driver not found " << endl;
                    }
                }else{
                    cout<<"order not found "<<endl;
                }
                }
                break;

            case 6:
            {
                string orderId;
                cout<<"enter order ID "<<endl;
                cin>>orderId;
                Order *thisOrder=nullptr;
                //search for order using order id
                for(int i=0; i<orderCount; i++){
                    if(orderId==orders[i]->getOrderId()){
                        thisOrder=orders[i];
                        break;
                    }
                }
            int status;
            cout << "0:PENDING, 1:PREPARING, 2:OUT_FOR_DELIVERY, 3:DELIVERED, 4:CANCELLED" << endl;
            cout << "select status: "; 
            cin >> status;
            //update status static cast to OrderStatus
            if (status >= 0 && status <= 4) {
                thisOrder->updateStatus(static_cast<OrderStatus>(status));
                cout << "status updated " << endl;
            }
                break;
            }

            case 7:
            {
                //display info by order id
                string orderId;
                cout<<"enter order ID "<<endl;
                cin>>orderId;
                for(int i=0; i<orderCount; i++){
                    if(orderId==orders[i]->getOrderId()){
                        orders[i]->displayOrder();
                        break;
                    }
                }
                break;
            }

            case 8:
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
            case 9:
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
            case 10:
            {
                //validate number of orders
                if (orderCount < 2) { 
                    cout << "Need 2 orders to compare." << endl; 
                    break; }
                string id1, id2;

                int i1=-11,i2=-11;
                cout<<"enter which two order IDs"<<endl;
                cin>>id1>>id2;
                //search for index of orders
                for(int i=0; i<orderCount; i++){
                    if(id1==orders[i]->getOrderId()){
                        i1=i;
                    }
                    if(id2==orders[i]->getOrderId()){
                        i2=i;
                    }
                }
                //compare orders
                if (*orders[i1] > *orders[i2]) {
                    cout << orders[i1]->getOrderId() << " is more expensive " << endl;}
                else {
                    cout << orders[i2]->getOrderId() << " is more expensive or equal" << endl;}
            break;
            }

            case 11:
            {
                cout << "users: " << User::getTotalUsers() << " orders: " << Order::getTotalOrders() << endl; 
                break;
            }

            case 12:
                saveOrders(orders, orderCount);
                break;

            case 13:
            {
                saveDriver(drivers, driverCount);
                break;
            }

            case 14:
            {
                saveOrdersToBinary();
                break;
            }
            case 15:
            {
                int num;
                cout<<"enter record"<<endl;
                cin>>num;
                loadOrderFromBinary(num);
                break;
            }

            case 16:
                showBinaryFileStats();
                break;

            case 17:
                cout<<"exiting"<<endl;
                break;

            default:
                cout<<"invalid choice"<<endl;
            
        }
    } while (choice != 17);
    for(int i=0; i<customerCount; i++) delete customers[i];
    delete[] customers;
    for(int i=0; i<driverCount; i++) delete drivers[i];
    delete[] drivers;
    for(int i=0; i<orderCount; i++) delete orders[i];
    delete[] orders;
    return 0;
}