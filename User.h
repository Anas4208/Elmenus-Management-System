#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
private:
    std::string userId_;
    std::string name_;
    std::string phoneNumber_;
    static int totalUsers_;
    
public:
    User();
    explicit User(const std::string& userId, const std::string& name, const std::string& phoneNumber);
    virtual ~User();
    
    // Use default instead of explicit delete where appropriate
    User(const User& other) = default;
    User& operator=(const User& other) = default;
    User(User&& other) noexcept = default;
    User& operator=(User&& other) noexcept = default;
    
    virtual void displayInfo() const = 0;
    virtual double calculateEarnings() const = 0;
    
    static int getTotalUsers();
    std::string getUserId() const;
    std::string getName() const;
    std::string getPhoneNumber() const;
};

#endif
