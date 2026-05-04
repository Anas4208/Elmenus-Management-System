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

int User::totalUsers = 0;
//default constructor
User::User(){
    userId="";
    name="";
    phoneNumber="";
    totalUsers++;
}
//parameterized construtor
User::User(string u, string n, string p){
    userId=u;
    name=n;
    phoneNumber=p;
    totalUsers++;
}
//getters
int User::getTotalUsers(){return totalUsers;}
string User::getUserId() const { return userId; }
string User::getName() const { return name; }
string User::getPhoneNumber() const { return phoneNumber; }

User::~User() {};