#pragma once

#include <string>

class StudentSetItem
{
public:
    StudentSetItem();
    virtual ~StudentSetItem();

    int getId(){ return Id; }
    void setId(int id){ Id = id; }

    std::string getName(){ return Name; }
    void setName(std::string name){ Name = name; }

    int getNumberOfPeople(){ return NumberOfPeople; }
    void setNumberOfPeople(int numberOfPeople){ NumberOfPeople = numberOfPeople; }

    std::string getSchool(){ return School; }
    void setSchool(std::string school){ School = school; }

    //std::set stores its values in a sorted binary tree,
    //so it needs to know how to compare the values it holds.
    //By default it uses std::less as a comparison function,
    //which for un - specialized user defined types tries to call operator<.
    //So, the easiest way to tell the set how to compare your objects is
    //to define an operator< for your class :
    bool operator<(const StudentSetItem& ssItem) const
    {
        return Id < ssItem.Id;
    }

private:
    int Id;
    std::string Name;
    int NumberOfPeople;
    std::string School;
};
