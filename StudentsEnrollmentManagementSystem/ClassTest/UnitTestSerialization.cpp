#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Students Enrollment Management System/User.h"
#include "../Students Enrollment Management System/Users.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ClassTest
{
	TEST_CLASS(UnitTestSerialization)
	{
	public:
		
        TEST_METHOD(TestMethodUserSerialization)
		{
            User u1;
            u1.setName("admin");
            u1.setPassword("admin");

            User u2;
            u2.setName("xiaosi");
            u2.setPassword("xiaosi");

            Users users;
            users.addUser(u1);
            users.addUser(u2);

            CFile cFile;
            cFile.Open(L"user.txt", CFile::modeCreate | CFile::modeWrite);
            CArchive archive(&cFile, CArchive::store);

            users.Serialize(archive);

            archive.Close();
            cFile.Close();
		}

        TEST_METHOD(TestMethodUserDeserialization)
        {
            Users users;

            CFile cFile;
            cFile.Open(L"user.txt", CFile::modeRead);
            CArchive archive(&cFile, CArchive::load);

            users.Serialize(archive);

            archive.Close();
            cFile.Close();
        }
	};
}
