#include "stdafx.h"
#include "User.h"

IMPLEMENT_SERIAL(User, CObject, 1)

User::User()
{
}


User::~User()
{
}

void User::Serialize(CArchive& archive)
{
    CObject::Serialize(archive);

    if (archive.IsStoring())
    {
        archive << stringToCString(Name) << stringToCString(Password);
    }
    else
    {
        CString cName;
        CString cPassword;
        archive >> cName >> cPassword;
        Name = CStringTostring(cName);
        Password = CStringTostring(cPassword);
    }
}
