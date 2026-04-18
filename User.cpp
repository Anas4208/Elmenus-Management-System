/*Anas Mohamed gamal 20246022
Ziad Gawad 20246055
group G6*/
#include "User.h"

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