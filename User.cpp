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

User::User(const User& other) = default;
User& User::operator=(const User& other) = default;
User::User(User&& other) noexcept = default;
User& User::operator=(User&& other) noexcept = default;

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
