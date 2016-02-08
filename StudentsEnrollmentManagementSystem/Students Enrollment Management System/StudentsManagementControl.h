#pragma once

#include "AllStudents.h"
#include "Student.h"
#include "UndergraduateStudent.h"
#include "GraduateStudent.h"
#include "Classes.h"
#include "ClassItem.h"
#include "Courses.h"
#include "CourseItem.h"
#include "ClassesAssociationHolder.h"
#include "CoursesAssociationHolder.h"

class StudentsManagementControl
{
public:
    StudentsManagementControl();
    ~StudentsManagementControl();

    //LoadData
    void loadStudentsData();
    void loadCoursesData();
    void loadClassesData();

    //Student
    Student findStudentById(int id);

    //Course
    CourseItem findCourseById(int id);

    //Class
    ClassItem findClassById(int id);

    //AllStudents
    void addStudent(Student student);
    void deleteStudentById(int id);
    void updateStudnet(Student student);
    AllStudents& getStudents();

    //Courses
    void addCourse(CourseItem course);
    void deleteCourseById(int id);
    void updateCourse(CourseItem courseItem);
    Courses& getCourses();

    //Classes
    void addClass(ClassItem classItem);
    void deleteClassById(int id);
    void updateClass(ClassItem classItem);
    Classes& getClasses();

    //ClassesAssociations
    void studentAddClass(int studentId, int classId);
    void studentDeleteClass(int studnetId, int classId);

    //CoursesAssciations
    void studentAddCourse(int studentId, int courseId);
    void studentDeleteCourse(int studentId, int courseId);

private:
    AllStudents students;
    Courses courses;
    Classes classes;

    ClassesAssociation classesAssociation;
    ClassesAssociationHolder classesAssociationHolder;
    CoursesAssociationHolder coursesAssociationHolder;
};
