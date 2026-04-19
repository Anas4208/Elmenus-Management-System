#include "User.h"
#include <utility>

int User::totalUsers_ = 0;

User::User() : userId_(""), name_(""), phoneNumber_("") {
    totalUsers_++;
}

User::User(const std::string& userId, const std::string& name, const std::string& phoneNumber)
    : userId_(userId), name_(name), phoneNumber_(phoneNumber) {
    totalUsers_++;
}

// Copy constructor
User::User(const User& other)
    : userId_(other.userId_), name_(other.name_), phoneNumber_(other.phoneNumber_) {
    totalUsers_++;
}

// Copy assignment operator
User& User::operator=(const User& other) {
    if (this != &other) {
        userId_ = other.userId_;
        name_ = other.name_;
        phoneNumber_ = other.phoneNumber_;
    }
    return *this;
}

// Move constructor
User::User(User&& other) noexcept
    : userId_(std::move(other.userId_)), 
      name_(std::move(other.name_)), 
      phoneNumber_(std::move(other.phoneNumber_)) {
    totalUsers_++;
}

// Move assignment operator
User& User::operator=(User&& other) noexcept {
    if (this != &other) {
        userId_ = std::move(other.userId_);
        name_ = std::move(other.name_);
        phoneNumber_ = std::move(other.phoneNumber_);
    }
    return *this;
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
