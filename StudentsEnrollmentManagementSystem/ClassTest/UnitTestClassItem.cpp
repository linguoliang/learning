#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Students Enrollment Management System/ClassItem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework; 
using namespace std;

namespace ClassTest
{
    TEST_CLASS(UnitTestClassItem)
	{
	public:
		
        TEST_METHOD(TestMethodClassItem)
		{
            int id = 1;
            string name = "Class 1";

            ClassItem c;
            c.setId(id);
            c.setName(name);

            Assert::AreEqual(c.getId(), id);
            Assert::AreEqual(c.getName(), name);

            StudentSetItem* s = new ClassItem;
            s->setId(id);
            s->setName(name);

            Assert::AreEqual(s->getId(), id);
            Assert::AreEqual(s->getName(), name);
		}
	};
}
