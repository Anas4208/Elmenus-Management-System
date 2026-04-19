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
    
    // Copy constructor and copy assignment
    User(const User& other);
    User& operator=(const User& other);
    
    // Move constructor and move assignment
    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;
    
    virtual void displayInfo() const = 0;
    virtual double calculateEarnings() const = 0;
    
    static int getTotalUsers();
    std::string getUserId() const;
    std::string getName() const;
    std::string getPhoneNumber() const;
};

#endif
