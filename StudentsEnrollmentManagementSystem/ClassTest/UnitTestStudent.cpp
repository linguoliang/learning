#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Students Enrollment Management System/Student.h"
#include "../Students Enrollment Management System/UndergraduateStudent.h"
#include "../Students Enrollment Management System/GraduateStudent.h"
#include <string>
#include <set>
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ClassTest
{
    TEST_CLASS(UnitTestStudent)
    {
    public:

        TEST_METHOD(TestMethodStudent)
        {
            int id = 123;
            string firstName = "Si";
            string lastName = "Xiao";
            string sex = "F";
            string campusAddress = "楸苑";
            string homeAddress = "中国";
            string provinceCity = "不知道";
            tm admissionTime;
            admissionTime.tm_mday = 1;
            admissionTime.tm_mon = 9;
            admissionTime.tm_year = 2012;

            UndergraduateStudent u;
            u.setId(id);
            u.setFirstName(firstName);
            u.setLastName(lastName);
            u.setSex(sex);
            u.setCampusAddress(campusAddress);
            u.setHomeAddress(homeAddress);
            u.setProvinceCity(provinceCity);
            u.setAdmissionTime(admissionTime);

            Assert::AreEqual(u.getId(), id);
            Assert::AreEqual(u.getFirstName(), firstName);
            Assert::AreEqual(u.getLastName(), lastName);
            Assert::AreEqual(u.getSex(), sex);
            Assert::AreEqual(u.getCampusAddress(), campusAddress);
            Assert::AreEqual(u.getHomeAddress(), homeAddress);
            Assert::AreEqual(u.getAdmissionTime().tm_mday, admissionTime.tm_mday);
            Assert::AreEqual(u.getAdmissionTime().tm_mon, admissionTime.tm_mon);
            Assert::AreEqual(u.getAdmissionTime().tm_year, admissionTime.tm_year);
        }

        TEST_METHOD(TestMethodStudentTypeCast)
        {
            int id = 123;
            string firstName = "Si";
            string lastName = "Xiao";
            string sex = "F";
            string campusAddress = "楸苑";
            string homeAddress = "中国";
            string provinceCity = "不知道";
            tm admissionTime;
            admissionTime.tm_mday = 1;
            admissionTime.tm_mon = 9;
            admissionTime.tm_year = 2012;

            UndergraduateStudent u;
            u.setId(id);
            u.setFirstName(firstName);
            u.setLastName(lastName);
            u.setSex(sex);
            u.setCampusAddress(campusAddress);
            u.setHomeAddress(homeAddress);
            u.setProvinceCity(provinceCity);
            u.setAdmissionTime(admissionTime);

            //normal
            {
                Student* s = &u;
                UndergraduateStudent* ugs = dynamic_cast<UndergraduateStudent*>(s);
                Assert::IsNotNull(ugs);

                GraduateStudent* gs = dynamic_cast<GraduateStudent*>(s);
                Assert::IsNull(gs);

                Logger::WriteMessage(typeid(u).name());
                Logger::WriteMessage(typeid(*s).name());
            }

            //const
            {
                const Student* cs = &u;
                Student* s = const_cast<Student*>(cs);

                UndergraduateStudent* ugs = dynamic_cast<UndergraduateStudent*>(s);
                Assert::IsNotNull(ugs);

                GraduateStudent* gs = dynamic_cast<GraduateStudent*>(s);
                Assert::IsNull(gs);
            }

            Assert::AreEqual(std::string("本科生"), getStudentType(&u));
        }

        TEST_METHOD(TestMethodSetStudentTypeCast)
        {
            string firstName = "Si";
            string lastName = "Xiao";
            string sex = "F";
            string campusAddress = "楸苑";
            string homeAddress = "中国";
            string provinceCity = "不知道";
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
            u1.setCampusAddress(campusAddress);
            u1.setHomeAddress(homeAddress);
            u1.setProvinceCity(provinceCity);
            u1.setAdmissionTime(admissionTime);

            //g1
            int gid1 = 222;

            GraduateStudent g1;
            g1.setId(gid1);
            g1.setFirstName(firstName);
            g1.setLastName(lastName);
            g1.setSex(sex);
            g1.setCampusAddress(campusAddress);
            g1.setHomeAddress(homeAddress);
            g1.setProvinceCity(provinceCity);
            g1.setAdmissionTime(admissionTime);

            set<Student> setStudents;

            setStudents.insert(u1);
            setStudents.insert(g1);

            auto setStudentsIterator = setStudents.begin();
            Student s = *setStudentsIterator;

            Student* ps = &s;
            UndergraduateStudent* pugs = dynamic_cast<UndergraduateStudent*>(ps);
            Assert::IsNotNull(pugs);

            GraduateStudent* pgs = dynamic_cast<GraduateStudent*>(ps);
            //Assert::IsNull(pgs);

            Logger::WriteMessage(typeid(u1).name());
            Logger::WriteMessage(typeid(s).name());
        }

        std::string getStudentType(const Student* student)
        {
            Student* s = const_cast<Student*>(student);

            UndergraduateStudent* ugs = dynamic_cast<UndergraduateStudent*>(s);
            GraduateStudent* gs = dynamic_cast<GraduateStudent*>(s);

            if (ugs != nullptr && gs == nullptr)
            {
                return "本科生";
            }
            else if (ugs == nullptr && gs != nullptr)
            {
                return "研究生";
            }
            return nullptr;
        }
    };
}
