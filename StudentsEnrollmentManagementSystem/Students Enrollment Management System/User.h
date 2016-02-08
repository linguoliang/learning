#pragma once

#include <string>
#include "Utilities.h"

class User : public CObject
{
public:
    User();
    ~User();

    void setName(std::string name){ Name = name; }
    std::string getName(){ return Name; }

    void setPassword(std::string password){ Password = password; }
    std::string getPassword(){ return Password; }

    void Serialize(CArchive& archive);

    User(const User &user)
    {
        Name = user.Name;
        Password = user.Password;
    }

protected:
    DECLARE_SERIAL(User)
    std::string Name;
    std::string Password;
};
