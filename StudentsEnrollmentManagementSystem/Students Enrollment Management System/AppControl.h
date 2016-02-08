#pragma once

#include "User.h"
#include "Users.h"

#include "StudentsManagementControl.h"

class AppControl :
    public StudentsManagementControl
{
public:
    AppControl();
    ~AppControl();

    //LoadData
    void loadUserInfo();

    //verify user
    bool verifyUser(User user);

private:
    Users users;
};
