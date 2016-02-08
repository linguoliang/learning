#pragma once

#include <string>
#include "Student.h"
#include "GraduateStudent.h"
#include "UndergraduateStudent.h"

#define WM_Students_Data_Init (WM_USER + 100)
#define WM_Courses_Data_Init (WM_USER + 101)
#define WM_Classes_Data_Init (WM_USER + 102)

#define WM_Update_StudentInfo (WM_USER + 103)
#define WM_Update_CourseInfo (WM_USER + 104)
#define WM_Update_ClassInfo (WM_USER + 104)

#define m_error -1
#define Man std::string("男")
#define Woman std::string("女")
#define GStudent std::string("研究生")
#define UGStuednt std::string("本科生")

//view mode
enum ViewMode
{
    Viewing,
    Editing,
    Newing
};

struct ViewInfo
{
    int nItem;
    ViewMode mode;
};

LPWSTR stringToLPWSTR(std::string str);
std::string CStringTostring(CString cstring);
CString stringToCString(std::string str);
SYSTEMTIME tmToSYSTEMTIME(std::tm time);
std::tm SYSTEMTIMETotm(SYSTEMTIME);
std::string getStudentType(const Student* student);
