#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Students Enrollment Management System/ClassItem.h"
#include "../Students Enrollment Management System/Classes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ClassTest
{
    TEST_CLASS(UnitTestClasses)
	{
	public:
		
		TEST_METHOD(TestMethodClasses)
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

            Assert::AreEqual(5, cs.getSetSize());
            cs.deleteSetItem(c4);
            Assert::AreEqual(4, cs.getSetSize());
            cs.deleteStudentSetItemById(id3);
            Assert::AreEqual(3, cs.getSetSize());

            auto csSet = cs.getSet();
            Assert::AreEqual((int)csSet.size(), cs.getSetSize());

            StudentSetItem s = cs.findStudentSetItemById(id2);
            Assert::AreEqual(s.getId(), id2);
            Assert::AreEqual(s.getName(), name2);
		}
	};
}
