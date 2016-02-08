#pragma once

#include <set>
#include <algorithm>
#include "Student.h"
#include "TSet.h"

class AllStudents :
    public TSet<Student>
{
public:
    AllStudents();
    ~AllStudents();

    void deleteStudentById(int id);
    Student findStudentById(int id);
};
