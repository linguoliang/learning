#include "stdafx.h"
#include "StudentsManagementControl.h"


StudentsManagementControl::StudentsManagementControl()
{
    this->loadStudentsData();
    this->loadCoursesData();
    this->loadClassesData();
}


StudentsManagementControl::~StudentsManagementControl()
{
}


//LoadData
void StudentsManagementControl::loadStudentsData()
{
    //TODO: implement IDataAccess
    std::string firstName = "Si";
    std::string lastName = "Xiao";
    std::string sex = "女";
    std::string school = "软件学院";
    std::string campusAddress = "楸苑";
    std::string homeAddress = "中国";
    std::string provinceCity = "不知道";
    tm admissionTime;
    admissionTime.tm_mday = 1;
    admissionTime.tm_mon = 9;
    admissionTime.tm_year = 2012;

    //u1
    int uid1 = 111;

    UndergraduateStudent u1;
    u1.setId(uid1);
    u1.setFirstName(firstName);
    u1.setLastName(lastName);
    u1.setSex(sex);
    u1.setSchool(school);
    u1.setCampusAddress(campusAddress);
    u1.setHomeAddress(homeAddress);
    u1.setProvinceCity(provinceCity);
    u1.setAdmissionTime(admissionTime);

    //u2
    int uid2 = 222;

    UndergraduateStudent u2;
    u2.setId(uid2);
    u2.setFirstName(firstName);
    u2.setLastName(lastName);
    u2.setSex(sex);
    u2.setSchool(school);
    u2.setCampusAddress(campusAddress);
    u2.setHomeAddress(homeAddress);
    u2.setProvinceCity(provinceCity);
    u2.setAdmissionTime(admissionTime);

    //u3
    int uid3 = 333;

    UndergraduateStudent u3;
    u3.setId(uid3);
    u3.setFirstName(firstName);
    u3.setLastName(lastName);
    u3.setSex(sex);
    u3.setSchool(school);
    u3.setCampusAddress(campusAddress);
    u3.setHomeAddress(homeAddress);
    u3.setProvinceCity(provinceCity);
    u3.setAdmissionTime(admissionTime);

    //u4
    int uid4 = 444;

    UndergraduateStudent u4;
    u4.setId(uid4);
    u4.setFirstName(firstName);
    u4.setLastName(lastName);
    u4.setSex(sex);
    u4.setSchool(school);
    u4.setCampusAddress(campusAddress);
    u4.setHomeAddress(homeAddress);
    u4.setProvinceCity(provinceCity);
    u4.setAdmissionTime(admissionTime);

    //u4
    int uid5 = 555;

    UndergraduateStudent u5;
    u5.setId(uid5);
    u5.setFirstName(firstName);
    u5.setLastName(lastName);
    u5.setSex(sex);
    u5.setSchool(school);
    u5.setCampusAddress(campusAddress);
    u5.setHomeAddress(homeAddress);
    u5.setProvinceCity(provinceCity);
    u5.setAdmissionTime(admissionTime);

    ////////////////////////////

    int gid1 = 666;
    std::string research = "多核数据结构";

    GraduateStudent g1;
    g1.setId(gid1);
    g1.setFirstName(firstName);
    g1.setLastName(lastName);
    g1.setSex(sex);
    g1.setSchool(school);
    g1.setCampusAddress(campusAddress);
    g1.setHomeAddress(homeAddress);
    g1.setProvinceCity(provinceCity);
    g1.setAdmissionTime(admissionTime);
    g1.setResearch(research);

    int gid2 = 777;

    GraduateStudent g2;
    g2.setId(gid2);
    g2.setFirstName(firstName);
    g2.setLastName(lastName);
    g2.setSex(sex);
    g2.setSchool(school);
    g2.setCampusAddress(campusAddress);
    g2.setHomeAddress(homeAddress);
    g2.setProvinceCity(provinceCity);
    g2.setAdmissionTime(admissionTime);
    g2.setResearch(research);

    ////////////////////////////

    this->addStudent(u1);
    this->addStudent(u2);
    this->addStudent(u3);
    this->addStudent(u4);
    this->addStudent(u5);
    this->addStudent(u1);
    this->addStudent(u2);
}

void StudentsManagementControl::loadCoursesData()
{
    //TODO: implement IDataAccess
    std::string name = "C++";
    std::string school = "软件学院";

    CourseItem c1;
    int id1 = 1;
    c1.setId(id1);
    c1.setName(name);
    c1.setNumberOfPeople(120);
    c1.setSchool(school);

    CourseItem c2;
    int id2 = 2;
    c2.setId(id2);
    c2.setName(name);
    c2.setNumberOfPeople(110);
    c2.setSchool(school);

    CourseItem c3;
    int id3 = 3;
    c3.setId(id3);
    c3.setName(name);
    c3.setNumberOfPeople(200);
    c3.setSchool(school);


    CourseItem c4;
    int id4 = 4;
    c4.setId(id4);
    c4.setName(name);
    c4.setNumberOfPeople(90);
    c4.setSchool(school);

    CourseItem c5;
    int id5 = 5;
    c5.setId(id5);
    c5.setName(name);
    c5.setNumberOfPeople(100);
    c5.setSchool(school);

    courses.addSetItem(c1);
    courses.addSetItem(c2);
    courses.addSetItem(c3);
    courses.addSetItem(c4);
    courses.addSetItem(c5);
}

void StudentsManagementControl::loadClassesData()
{
    //TODO: implement IDataAccess
    std::string name = "网络工程";
    std::string school = "软件学院";

    ClassItem c1;
    int id1 = 1;
    c1.setId(id1);
    c1.setName(name);
    c1.setNumberOfPeople(120);
    c1.setSchool(school);

    ClassItem c2;
    int id2 = 2;
    c2.setId(id2);
    c2.setName(name);
    c2.setNumberOfPeople(110);
    c2.setSchool(school);

    ClassItem c3;
    int id3 = 3;
    c3.setId(id3);
    c3.setName(name);
    c3.setNumberOfPeople(200);
    c3.setSchool(school);


    ClassItem c4;
    int id4 = 4;
    c4.setId(id4);
    c4.setName(name);
    c4.setNumberOfPeople(90);
    c4.setSchool(school);

    ClassItem c5;
    int id5 = 5;
    c5.setId(id5);
    c5.setName(name);
    c5.setNumberOfPeople(100);
    c5.setSchool(school);

    classes.addSetItem(c1);
    classes.addSetItem(c2);
    classes.addSetItem(c3);
    classes.addSetItem(c4);
    classes.addSetItem(c5);
}

//Student
Student StudentsManagementControl::findStudentById(int id)
{
    return students.findStudentById(id);
}

//Course
CourseItem StudentsManagementControl::findCourseById(int id)
{
    return courses.findStudentSetItemById(id);
}

//Class
ClassItem StudentsManagementControl::findClassById(int id)
{
    return classes.findStudentSetItemById(id);
}

//AllStudents
void StudentsManagementControl::addStudent(Student student)
{
    students.addSetItem(student);
}

void StudentsManagementControl::deleteStudentById(int id)
{
    students.deleteStudentById(id);
}

void StudentsManagementControl::updateStudnet(Student student)
{
    this->deleteStudentById(student.getId());
    this->addStudent(student);
}

AllStudents& StudentsManagementControl::getStudents()
{
    return students;
}

//Courses
void StudentsManagementControl::addCourse(CourseItem course)
{
    courses.addSetItem(course);
}

void StudentsManagementControl::deleteCourseById(int id)
{
    courses.deleteStudentSetItemById(id);
}

void StudentsManagementControl::updateCourse(CourseItem courseItem)
{
    this->deleteCourseById(courseItem.getId());
    this->addCourse(courseItem);
}

Courses& StudentsManagementControl::getCourses()
{
    return courses;
}

//Classes
void StudentsManagementControl::addClass(ClassItem classItem)
{
    classes.addSetItem(classItem);
}

void StudentsManagementControl::deleteClassById(int id)
{
    classes.deleteStudentSetItemById(id);
}

void StudentsManagementControl::updateClass(ClassItem classItem)
{
    this->deleteClassById(classItem.getId());
    this->addClass(classItem);
}

Classes& StudentsManagementControl::getClasses()
{
    return classes;
}

void StudentsManagementControl::studentAddClass(int studentId, int classId)
{
    Student student = students.findStudentById(studentId);
    ClassItem classItem = classes.findStudentSetItemById(classId);

    classesAssociationHolder.addAssociation(classItem, student, classesAssociation);
}

void StudentsManagementControl::studentDeleteClass(int studentId, int classId)
{
    Student student = students.findStudentById(studentId);
    ClassItem classItem = classes.findStudentSetItemById(classId);

    classesAssociationHolder.removeAssociation(classItem, student);
}


void StudentsManagementControl::studentAddCourse(int studentId, int courseId)
{
    Student student = students.findStudentById(studentId);
    CourseItem courseItem = courses.findStudentSetItemById(courseId);

    coursesAssociationHolder.addAssociation(courseItem, student, classesAssociation);
}

void StudentsManagementControl::studentDeleteCourse(int studentId, int courseId)
{
    Student student = students.findStudentById(studentId);
    CourseItem courseItem = courses.findStudentSetItemById(courseId);

    coursesAssociationHolder.removeAssociation(courseItem, student);
}
