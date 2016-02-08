#include "stdafx.h"
#include "StudentSetAssociationHolder.h"

StudentSetAssociationHolder::StudentSetAssociationHolder()
{
}

StudentSetAssociationHolder::~StudentSetAssociationHolder()
{
}

void StudentSetAssociationHolder::addAssociation(StudentSetItem studentSetItem, Student student, ClassesAssociation classassociation)
{
    std::map<StudentSetItem, std::map<Student, ClassesAssociation>>::iterator classMapIterator = associationClass.find(studentSetItem);

    std::map<Student, ClassesAssociation> classMap;

    std::map<StudentSetItem, std::map<Student, ClassesAssociation>>::iterator associationClassIterator;
    if (classMapIterator == associationClass.end())
    {
        classMap = std::map<Student, ClassesAssociation>();
        auto classMapInsertRet = associationClass.insert(std::pair<StudentSetItem, std::map<Student, ClassesAssociation>>(studentSetItem, classMap));
        classMap = (*classMapInsertRet.first).second;
        associationClassIterator = classMapInsertRet.first;
    }
    else
    {
        classMap = classMapIterator->second;
        associationClassIterator = classMapIterator;
    }

    auto associationClassBeginIterator = associationClass.begin();
    int distC = std::distance(associationClassBeginIterator, associationClassIterator);
    (*std::next(associationClassBeginIterator, distC)).second.insert(std::pair<Student, ClassesAssociation>(student, classassociation));

    //todo second insert doesn't work, find out why!!!
    //(*associationClass.begin()).second.insert(std::pair<Student, ClassesAssociation>(student, classassociation));
    //classMap.insert(std::pair<Student, ClassesAssociation>(student, classassociation));

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::map<Student, std::map<StudentSetItem, ClassesAssociation>>::iterator studentMapIterator = associationStudent.find(student);

    std::map<StudentSetItem, ClassesAssociation> studentMap;

    std::map<Student, std::map<StudentSetItem, ClassesAssociation>>::iterator associationStudentIterator;
    if (studentMapIterator == associationStudent.end())
    {
        studentMap = std::map<StudentSetItem, ClassesAssociation>();
        auto studentMapInsertRet = associationStudent.insert(std::pair<Student, std::map<StudentSetItem, ClassesAssociation>>(student, studentMap));
        studentMap = (*studentMapInsertRet.first).second;
        associationStudentIterator = studentMapInsertRet.first;
    }
    else
    {
        studentMap = studentMapIterator->second;
        associationStudentIterator = studentMapIterator;
    }

    auto associationStudentBeginIterator = associationStudent.begin();
    int distS = std::distance(associationStudentBeginIterator, associationStudentIterator);
    (*std::next(associationStudentBeginIterator, distS)).second.insert(std::pair<StudentSetItem, ClassesAssociation>(studentSetItem, classassociation));

    //todo insert doesn't work, find out why!!!
    //studentMap.insert(std::pair<StudentSetItem, ClassesAssociation>(studentSetItem, classassociation));
}

ClassesAssociation StudentSetAssociationHolder::getAssociation(StudentSetItem studentSetItem, Student student)
{
    std::map<StudentSetItem, std::map<Student, ClassesAssociation>>::iterator classMapIterator = associationClass.find(studentSetItem);
    if (classMapIterator == associationClass.end())
    {
        return ClassesAssociation();
    }
    else
    {
        std::map<Student, ClassesAssociation> classMap = classMapIterator->second;
        std::map<Student, ClassesAssociation>::iterator studentIterator = classMap.find(student);
        return studentIterator->second;
    }
}

std::map<Student, ClassesAssociation> StudentSetAssociationHolder::getAssociationClass(StudentSetItem studentSetItem)
{
    std::map<StudentSetItem, std::map<Student, ClassesAssociation>>::iterator classMapIterator = associationClass.find(studentSetItem);

    if (classMapIterator == associationClass.end())
    {
        return std::map<Student, ClassesAssociation>();
    }
    else
    {
        return classMapIterator->second;
    }
}

std::map<StudentSetItem, ClassesAssociation> StudentSetAssociationHolder::getAssociationStudent(Student student)
{
    std::map<Student, std::map<StudentSetItem, ClassesAssociation>>::iterator studentMapIterator
        = associationStudent.find(student);

    if (studentMapIterator == associationStudent.end())
    {
        return std::map<StudentSetItem, ClassesAssociation>();
    }
    else
    {
        return studentMapIterator->second;
    }
}

void StudentSetAssociationHolder::removeAssociation(StudentSetItem studentSetItem, Student student)
{
    std::map<Student, ClassesAssociation> classMap = getAssociationClass(studentSetItem);
    std::map<StudentSetItem, ClassesAssociation> studentMap = getAssociationStudent(student);
    classMap.erase(student);
    studentMap.erase(studentSetItem);
}
