/*Anas Mohamed gamal 20246022
Ziad Gawad 20246055
group G6*/
#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
using namespace std;

class User{
    protected:
    string userId;
    string name;
    string phoneNumber;
    static int totalUsers;
    public:
    User();
    User(string u, string n, string p);
    //pure virtual functions
    virtual void displayInfo()=0;
    virtual double calculateEarnings()=0;
    //getters
    static int getTotalUsers();
    string getUserId() const;
    string getName() const;
    string getPhoneNumber() const;

    virtual ~User();
};
#endif