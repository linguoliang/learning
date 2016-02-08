#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Students Enrollment Management System/AllStudents.h"
#include "../Students Enrollment Management System/UndergraduateStudent.h"
#include "../Students Enrollment Management System/GraduateStudent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ClassTest
{
	TEST_CLASS(UnitTestAllStudents)
	{
	public:
		
        TEST_METHOD(TestMethodAllStudents)
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

            //u2
            int uid2 = 222;

            UndergraduateStudent u2;
            u2.setId(uid2);
            u2.setFirstName(firstName);
            u2.setLastName(lastName);
            u2.setSex(sex);
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
            u5.setCampusAddress(campusAddress);
            u5.setHomeAddress(homeAddress);
            u5.setProvinceCity(provinceCity);
            u5.setAdmissionTime(admissionTime);

            AllStudents allStudents;
            allStudents.addSetItem(u1);
            allStudents.addSetItem(u2);
            allStudents.addSetItem(u3);
            allStudents.addSetItem(u4);
            allStudents.addSetItem(u5);

            Assert::AreEqual(5, allStudents.getSetSize());

            ////////////////////////////

            int gid1 = 666;

            GraduateStudent g1;
            g1.setId(gid1);
            g1.setFirstName(firstName);
            g1.setLastName(lastName);
            g1.setSex(sex);
            g1.setCampusAddress(campusAddress);
            g1.setHomeAddress(homeAddress);
            g1.setProvinceCity(provinceCity);
            g1.setAdmissionTime(admissionTime);

            ////////////////////////////

            allStudents.addSetItem(g1);

            Assert::AreEqual(6, allStudents.getSetSize());
		}

        TEST_METHOD(TestMethodAllStudentsTypeCast)
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

            AllStudents allStudents;
            allStudents.addSetItem(u1);
            allStudents.addSetItem(g1);

            set<Student> setStudents = allStudents.getSet();

            auto setStudentsIterator = setStudents.begin();
            Student s = *(setStudentsIterator);

            Student* ps = &s;
            UndergraduateStudent* pugs = dynamic_cast<UndergraduateStudent*>(ps);
            //Assert::IsNotNull(pugs);

            GraduateStudent* pgs = dynamic_cast<GraduateStudent*>(ps);
            //Assert::IsNull(pgs);
        }
	};
}
