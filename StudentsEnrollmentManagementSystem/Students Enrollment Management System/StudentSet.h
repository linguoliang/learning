#pragma once

#include <set>
#include <algorithm>
#include "StudentSetItem.h"
#include "TSet.h"

class StudentSet :
    public TSet<StudentSetItem>
{
public:
    StudentSet();
    ~StudentSet();

    void deleteStudentSetItemById(int id);
    StudentSetItem findStudentSetItemById(int id);
};
