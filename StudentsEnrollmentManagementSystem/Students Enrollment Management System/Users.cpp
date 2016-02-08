#include "stdafx.h"
#include "Users.h"

IMPLEMENT_SERIAL(Users, CObject, 1)

Users::Users()
{
}


Users::~Users()
{
}

void Users::addUser(User user)
{
    users.push_back(user);
}


bool Users::isContain(User user)
{
    if (std::find_if(users.begin(), users.end(),
        [&user](User tmp)
    {
        return (user.getName() == tmp.getName()) && (user.getPassword() == tmp.getPassword());
    })
        != users.end())
    {
        return true;
    }
    return false;
}

void Users::Serialize(CArchive& archive)
{
    CObject::Serialize(archive);

    if (archive.IsStoring())
    {
        archive << users.size();

        for (User user : users)
        {
            user.Serialize(archive);
        }
    }
    else
    {
        size_t size;
        archive >> size;
        
        for (size_t i = 0; i < size; i++)
        {
            User user;
            user.Serialize(archive);
            users.push_back(user);
        }
    }
}
