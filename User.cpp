// User.cpp
#include "User.h"

int User::totalUsers = 0;

User::User()
    : userId(""), name(""), phoneNumber("") {
    ++totalUsers;
}

User::User(const std::string& uid, const std::string& n, const std::string& phone)
    : userId(uid), name(n), phoneNumber(phone) {
    ++totalUsers;
}

// ✅ Fix 2: Copy constructor — increment counter for the new object
User::User(const User& other)
    : userId(other.userId), name(other.name), phoneNumber(other.phoneNumber) {
    ++totalUsers;
}

// ✅ Fix 2: Copy assignment — counter stays the same (object already exists)
User& User::operator=(const User& other) {
    if (this != &other) {
        userId      = other.userId;
        name        = other.name;
        phoneNumber = other.phoneNumber;
    }
    return *this;
}

// ✅ Fix 2: Move constructor — transfer data, increment counter for new object
User::User(User&& other) noexcept
    : userId(std::move(other.userId)),
      name(std::move(other.name)),
      phoneNumber(std::move(other.phoneNumber)) {
    ++totalUsers;
}

// ✅ Fix 2: Move assignment — counter stays the same (object already exists)
User& User::operator=(User&& other) noexcept {
    if (this != &other) {
        userId      = std::move(other.userId);
        name        = std::move(other.name);
        phoneNumber = std::move(other.phoneNumber);
    }
    return *this;
}

User::~User() {
    --totalUsers;
}

int         User::getTotalUsers()    { return totalUsers;   }
std::string User::getUserId()      const { return userId;      }
std::string User::getName()        const { return name;        }
std::string User::getPhoneNumber() const { return phoneNumber; }