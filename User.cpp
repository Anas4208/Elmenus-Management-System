#include "User.h"

int User::totalUsers_ = 0;

User::User() : userId_(""), name_(""), phoneNumber_("") {
    totalUsers_++;
}

User::User(const std::string& userId, const std::string& name, const std::string& phoneNumber)
    : userId_(userId), name_(name), phoneNumber_(phoneNumber) {
    totalUsers_++;
}

User::~User() {
    totalUsers_--;
}

int User::getTotalUsers() {
    return totalUsers_;
}

std::string User::getUserId() const {
    return userId_;
}

std::string User::getName() const {
    return name_;
}

std::string User::getPhoneNumber() const {
    return phoneNumber_;
}
