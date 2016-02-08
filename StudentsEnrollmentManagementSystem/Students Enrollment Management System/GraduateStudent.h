#pragma once
#include "Student.h"
class GraduateStudent :
    public Student
{
public:
    GraduateStudent();
    ~GraduateStudent();

    std::string getResearch(){ return Research; }
    void setResearch(std::string research){ Research = research; }

private:
    std::string Research;
};

