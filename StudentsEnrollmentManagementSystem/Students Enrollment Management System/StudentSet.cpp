#include "stdafx.h"
#include "StudentSet.h"

StudentSet::StudentSet()
{
}


StudentSet::~StudentSet()
{
}

void StudentSet::deleteStudentSetItemById(int id)
{
    auto pt = std::find_if(Set.begin(), Set.end(), [id](StudentSetItem item){ return item.getId() == id; });
    Set.erase(pt);
}

StudentSetItem StudentSet::findStudentSetItemById(int id)
{
    auto pt = std::find_if(Set.begin(), Set.end(), [id](StudentSetItem item){ return item.getId() == id; });
    return *pt;
}
