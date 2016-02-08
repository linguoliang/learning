#include "stdafx.h"
#include "Classes.h"


Classes::Classes()
{
}


Classes::~Classes()
{
}

ClassItem Classes::findStudentSetItemById(int id)
{
    StudentSetItem studentSetItem = StudentSet::findStudentSetItemById(id);

    //TODO_Emergency potential bug
    ClassItem* classItem = reinterpret_cast<ClassItem*>(&studentSetItem);

    return *classItem;
}