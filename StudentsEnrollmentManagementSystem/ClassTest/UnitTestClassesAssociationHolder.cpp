#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Students Enrollment Management System/ClassItem.h"
#include "../Students Enrollment Management System/Classes.h"
#include "../Students Enrollment Management System/UndergraduateStudent.h"
#include "../Students Enrollment Management System/ClassesAssociationHolder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ClassTest
{
	TEST_CLASS(UnitTestClassesAssociationHolder)
	{
	public:
		
        TEST_METHOD(TestMethodClassesAssociationHolder)
        {
            ClassItem c1;
            int id1 = 1;
            string name1 = "Class 1";
            c1.setId(id1);
            c1.setName(name1);

            ClassItem c2;
            int id2 = 2;
            string name2 = "Class 2";
            c2.setId(id2);
            c2.setName(name2);

            ClassItem c3;
            int id3 = 3;
            string name3 = "Class 3";
            c3.setId(id3);
            c3.setName(name3);

            ClassItem c4;
            int id4 = 4;
            string name4 = "Class 4";
            c4.setId(id4);
            c4.setName(name4);

            ClassItem c5;
            int id5 = 5;
            string name5 = "Class 5";
            c5.setId(id5);
            c5.setName(name5);

            Classes cs;
            cs.addSetItem(c1);
            cs.addSetItem(c2);
            cs.addSetItem(c3);
            cs.addSetItem(c4);
            cs.addSetItem(c5);

            int uid1 = 111;
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

            UndergraduateStudent u1;
            u1.setId(uid1);
            u1.setFirstName(firstName);
            u1.setLastName(lastName);
            u1.setSex(sex);
            u1.setCampusAddress(campusAddress);
            u1.setHomeAddress(homeAddress);
            u1.setProvinceCity(provinceCity);
            u1.setAdmissionTime(admissionTime);

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

            ClassesAssociationHolder csa;
            ClassesAssociation uca;

            csa.addAssociation(c1, u1, uca);
            csa.addAssociation(c1, u2, uca);
            csa.addAssociation(c2, u2, uca);

            auto studentMap = csa.getAssociationClass(c1);
            auto classMap = csa.getAssociationStudent(u1);

            Assert::AreEqual(studentMap.size(), (size_t)2);
            Logger::WriteMessage(to_string(studentMap.size()).c_str());
		}

        TEST_METHOD(TestMethodClassesAssociationHolder_getAssociation)
        {
            ClassItem c1;
            int id1 = 1;
            string name1 = "Class 1";
            c1.setId(id1);
            c1.setName(name1);

            ClassItem c2;
            int id2 = 2;
            string name2 = "Class 2";
            c2.setId(id2);
            c2.setName(name2);

            ClassItem c3;
            int id3 = 3;
            string name3 = "Class 3";
            c3.setId(id3);
            c3.setName(name3);

            ClassItem c4;
            int id4 = 4;
            string name4 = "Class 4";
            c4.setId(id4);
            c4.setName(name4);

            ClassItem c5;
            int id5 = 5;
            string name5 = "Class 5";
            c5.setId(id5);
            c5.setName(name5);

            Classes cs;
            cs.addSetItem(c1);
            cs.addSetItem(c2);
            cs.addSetItem(c3);
            cs.addSetItem(c4);
            cs.addSetItem(c5);

            int uid1 = 111;
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

            UndergraduateStudent u1;
            u1.setId(uid1);
            u1.setFirstName(firstName);
            u1.setLastName(lastName);
            u1.setSex(sex);
            u1.setCampusAddress(campusAddress);
            u1.setHomeAddress(homeAddress);
            u1.setProvinceCity(provinceCity);
            u1.setAdmissionTime(admissionTime);

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

            ClassesAssociationHolder csa;
            ClassesAssociation uca;

            csa.addAssociation(c1, u1, uca);
            csa.addAssociation(c1, u2, uca);
            csa.addAssociation(c2, u2, uca);

            auto studentMap = csa.getAssociationClass(c1);
            auto classMap = csa.getAssociationStudent(u1);

            //association between c3 and u1 doesn't exist
            auto association = csa.getAssociation(c3, u1);
            //Assert::IsNull(&association);
        }
	};
}
