#include "stdafx.h"
#include "Courses.h"


Courses::Courses()
{
}


Courses::~Courses()
{
}

CourseItem Courses::findStudentSetItemById(int id)
{
    StudentSetItem studentSetItem = StudentSet::findStudentSetItemById(id);

    //TODO_Emergency potential bug
    CourseItem* courseItem = reinterpret_cast<CourseItem*>(&studentSetItem);

    return *courseItem;
}
