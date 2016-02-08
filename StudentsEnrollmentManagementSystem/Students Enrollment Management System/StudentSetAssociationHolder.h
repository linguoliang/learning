#pragma once

#include <map>
#include <set>
#include <iterator>
#include "StudentSetItem.h"
#include "Student.h"

class ClassesAssociation
{
public:
    ClassesAssociation(){};
    ~ClassesAssociation(){};
};

class StudentSetAssociationHolder
{
public:
    StudentSetAssociationHolder();
    ~StudentSetAssociationHolder();

    void addAssociation(StudentSetItem studentSetItem, Student student, ClassesAssociation classesAssociation);
    ClassesAssociation getAssociation(StudentSetItem studentSetItem, Student student);
    std::map<Student, ClassesAssociation> getAssociationClass(StudentSetItem studentSetItem);
    std::map<StudentSetItem, ClassesAssociation> getAssociationStudent(Student student);
    void removeAssociation(StudentSetItem studentSetItem, Student student);

private:
    std::map<StudentSetItem, std::map<Student, ClassesAssociation>> associationClass;
    std::map<Student, std::map<StudentSetItem, ClassesAssociation>> associationStudent;
};
