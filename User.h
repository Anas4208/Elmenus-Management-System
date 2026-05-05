#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string userId;
    std::string name;
    std::string phoneNumber;
    static int totalUsers;

public:
    User();
    User(const std::string& uid, const std::string& n, const std::string& phone);
    virtual ~User();

    virtual void   displayInfo()       const = 0;
    virtual double calculateEarnings() const = 0;

    static int getTotalUsers();

    std::string getUserId()     const;
    std::string getName()       const;
    std::string getPhoneNumber() const;
};

#endif // USER_H
