#pragma once

#include "StudentSet.h"
#include "CourseItem.h"

class Courses :
    public StudentSet
{
public:
    Courses();
    ~Courses();

    CourseItem findStudentSetItemById(int id);
};

