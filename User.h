// User.h
#ifndef USER_H
#define USER_H

#include <string>

class User {
private:                          // ✅ Fix 1: private instead of protected
    std::string userId;
    std::string name;
    std::string phoneNumber;
    static int totalUsers;

public:
    User();
    User(const std::string& uid, const std::string& n, const std::string& phone);

    // ✅ Fix 2: Explicitly define copy constructor & copy assignment operator
    User(const User& other);
    User& operator=(const User& other);

    // ✅ Fix 2: Explicitly define move constructor & move assignment operator
    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;

    virtual ~User();

    virtual void   displayInfo()       const = 0;
    virtual double calculateEarnings() const = 0;

    static int getTotalUsers();

    std::string getUserId()      const;
    std::string getName()        const;
    std::string getPhoneNumber() const;
};

#endif // USER_H