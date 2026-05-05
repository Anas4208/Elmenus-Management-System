#include "User.h"

int User::totalUsers = 0;

User::User() : userId(""), name(""), phoneNumber("") {
    ++totalUsers;
}

User::User(const std::string& uid, const std::string& n, const std::string& phone)
    : userId(uid), name(n), phoneNumber(phone) {
    ++totalUsers;
}

User::~User() {
    --totalUsers;
}

int         User::getTotalUsers()   { return totalUsers;   }
std::string User::getUserId()     const { return userId;      }
std::string User::getName()       const { return name;        }
std::string User::getPhoneNumber() const { return phoneNumber; }
