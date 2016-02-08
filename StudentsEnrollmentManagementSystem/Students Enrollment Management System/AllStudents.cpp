#include "stdafx.h"
#include "AllStudents.h"


AllStudents::AllStudents()
{
}


AllStudents::~AllStudents()
{
}

void AllStudents::deleteStudentById(int id)
{
    auto pt = std::find_if(Set.begin(), Set.end(), [id](Student student){ return student.getId() == id; });
    Set.erase(pt);
}

Student AllStudents::findStudentById(int id)
{
    auto pt = std::find_if(Set.begin(), Set.end(), [id](Student student){ return student.getId() == id; });
    return *pt;
}
