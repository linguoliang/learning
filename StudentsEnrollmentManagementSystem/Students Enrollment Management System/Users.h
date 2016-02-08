#pragma once

#include <algorithm>
#include <vector>
#include "User.h"

class Users : public CObject
{
public:
    Users();
    ~Users();

    void addUser(User user);
    bool isContain(User user);
    void Serialize(CArchive& archive);

protected:
    DECLARE_SERIAL(Users)
    std::vector<User> users;
};

