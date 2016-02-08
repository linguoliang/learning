#include "stdafx.h"
#include "Utilities.h"

LPWSTR stringToLPWSTR(std::string str)
{
    return static_cast<LPWSTR>(CString(str.c_str()).AllocSysString());
}

std::string CStringTostring(CString cstring)
{
    CT2CA psz(cstring);
    return std::string(psz);
}

CString stringToCString(std::string str)
{
    return CString(str.c_str());
}

SYSTEMTIME tmToSYSTEMTIME(std::tm time)
{
    SYSTEMTIME sysTime;
    sysTime.wYear = time.tm_year;
    sysTime.wMonth = time.tm_mon;
    sysTime.wDay = time.tm_mday;
    sysTime.wHour = time.tm_hour;
    sysTime.wMinute = time.tm_min;
    sysTime.wSecond = time.tm_sec;

    return sysTime;
}

std::tm SYSTEMTIMETotm(SYSTEMTIME sysTime)
{
    std::tm time;
    time.tm_year = sysTime.wYear;
    time.tm_mon = sysTime.wMonth;
    time.tm_mday = sysTime.wDay;
    time.tm_hour = sysTime.wHour;
    time.tm_min = sysTime.wMinute;
    time.tm_sec = sysTime.wSecond;

    return time;
}

std::string getStudentType(const Student* student)
{
    Student* s = const_cast<Student*>(student);

    UndergraduateStudent* ugs = dynamic_cast<UndergraduateStudent*>(s);
    GraduateStudent* gs = dynamic_cast<GraduateStudent*>(s);

    if (ugs != nullptr && gs == nullptr)
    {
        return UGStuednt;
    }
    else if (ugs == nullptr && gs != nullptr)
    {
        return GStudent;
    }
    return "Ñ§Éú";
}
