#pragma once

#include "StudentSet.h"
#include "ClassItem.h"

class Classes :
    public StudentSet
{
public:
    Classes();
    ~Classes();

    ClassItem findStudentSetItemById(int id);
};
