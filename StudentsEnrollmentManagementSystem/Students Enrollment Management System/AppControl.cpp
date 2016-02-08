#include "stdafx.h"
#include "AppControl.h"


AppControl::AppControl()
{
}


AppControl::~AppControl()
{
}

bool AppControl::verifyUser(User user)
{
    if (users.isContain(user))
    {
        return true;
    }

    return false;
}
