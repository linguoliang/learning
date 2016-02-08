using System;
using System.Text;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Domain;

namespace UnitTests
{
    /// <summary>
    /// UnitTestDomainContacts 的摘要说明
    /// </summary>
    [TestClass]
    public class UnitTestDomainContacts
    {
        public UnitTestDomainContacts()
        {
            //
            //TODO:  在此处添加构造函数逻辑
            //
        }

        private TestContext testContextInstance;

        /// <summary>
        ///获取或设置测试上下文，该上下文提供
        ///有关当前测试运行及其功能的信息。
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region 附加测试特性
        //
        // 编写测试时，可以使用以下附加特性: 
        //
        // 在运行类中的第一个测试之前使用 ClassInitialize 运行代码
        // [ClassInitialize()]
        // public static void MyClassInitialize(TestContext testContext) { }
        //
        // 在类中的所有测试都已运行之后使用 ClassCleanup 运行代码
        // [ClassCleanup()]
        // public static void MyClassCleanup() { }
        //
        // 在运行每个测试之前，使用 TestInitialize 来运行代码
        // [TestInitialize()]
        // public void MyTestInitialize() { }
        //
        // 在每个测试运行完之后，使用 TestCleanup 来运行代码
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion

        [TestMethod]
        public void ContactsNew()
        {
            Contacts contacts = new Contacts();

            Assert.IsNotNull(contacts);
            Assert.AreEqual(1, contacts.GroupsAmount);
            Assert.AreEqual(0, contacts.PersonsAmount);
        }

        [TestMethod]
        public void ContactsAdd()
        {
            Contacts contacts = new Contacts();

            Group group1 = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group1.AddPerson(person1);

            Assert.AreEqual(1, group1.Amount);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group1.AddPerson(person2);

            Group group2 = new Group();

            string name3 = "chao";
            string company3 = "ynu";
            string position3 = "graduate";

            Person person3 = new Person { Name = name3, Company = company3, Position = position3 };

            group2.AddPerson(person3);

            Group group3 = new Group();

            string name4 = "maichao";
            string company4 = "ynu";
            string position4 = "student";

            Person person4 = new Person { Name = name4, Company = company4, Position = position4 };

            group3.AddPerson(person4);

            Assert.AreEqual(1, group3.Amount);

            string name5 = "mai";
            string company5 = "ynu";
            string position5 = "graduate";

            Person person5 = new Person { Name = name5, Company = company5, Position = position5 };

            group3.AddPerson(person5);

            contacts.AddGroup(group1);
            contacts.AddGroup(group2);
            contacts.AddGroup(group3);

            Assert.AreEqual(4, contacts.GroupsAmount);
            Assert.AreEqual(5, contacts.PersonsAmount);
        }

        [TestMethod]
        public void ContactsDelete()
        {
            Contacts contacts = new Contacts();

            Group group1 = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group1.AddPerson(person1);

            Assert.AreEqual(1, group1.Amount);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group1.AddPerson(person2);

            Group group2 = new Group();

            string name3 = "chao";
            string company3 = "ynu";
            string position3 = "graduate";

            Person person3 = new Person { Name = name3, Company = company3, Position = position3 };

            group2.AddPerson(person3);

            Group group3 = new Group();

            string name4 = "maichao";
            string company4 = "ynu";
            string position4 = "student";

            Person person4 = new Person { Name = name4, Company = company4, Position = position4 };

            group3.AddPerson(person4);

            Assert.AreEqual(1, group3.Amount);

            string name5 = "mai";
            string company5 = "ynu";
            string position5 = "graduate";

            Person person5 = new Person { Name = name5, Company = company5, Position = position5 };

            group3.AddPerson(person5);

            contacts.AddGroup(group1);
            contacts.AddGroup(group2);
            contacts.AddGroup(group3);

            contacts.DeleteGroup(group2);

            Assert.AreEqual(3, contacts.GroupsAmount);
            Assert.AreEqual(5, contacts.PersonsAmount);

            contacts.DeleteGroup(group3);

            Assert.AreEqual(2, contacts.GroupsAmount);
            Assert.AreEqual(5, contacts.PersonsAmount);
        }

        [TestMethod]
        public void ContactsSearchGroupById()
        {
            Contacts contacts = new Contacts();

            Group group1 = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group1.AddPerson(person1);

            Assert.AreEqual(1, group1.Amount);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group1.AddPerson(person2);

            Group group2 = new Group();

            string name3 = "chao";
            string company3 = "ynu";
            string position3 = "graduate";

            Person person3 = new Person { Name = name3, Company = company3, Position = position3 };

            group2.AddPerson(person3);

            Group group3 = new Group();

            string name4 = "maichao";
            string company4 = "ynu";
            string position4 = "student";

            Person person4 = new Person { Name = name4, Company = company4, Position = position4 };

            group3.AddPerson(person4);

            Assert.AreEqual(1, group3.Amount);

            string name5 = "mai";
            string company5 = "ynu";
            string position5 = "graduate";

            Person person5 = new Person { Name = name5, Company = company5, Position = position5 };

            group3.AddPerson(person5);

            contacts.AddGroup(group1);
            contacts.AddGroup(group2);
            contacts.AddGroup(group3);

            Group group = contacts.SearchGroupById(group2.Id);

            Assert.IsNotNull(group);
        }

        [TestMethod]
        public void ContactsGetGroups()
        {
            Contacts contacts = new Contacts();

            Group group1 = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group1.AddPerson(person1);

            Assert.AreEqual(1, group1.Amount);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group1.AddPerson(person2);

            Group group2 = new Group();

            string name3 = "chao";
            string company3 = "ynu";
            string position3 = "graduate";

            Person person3 = new Person { Name = name3, Company = company3, Position = position3 };

            group2.AddPerson(person3);

            Group group3 = new Group();

            string name4 = "maichao";
            string company4 = "ynu";
            string position4 = "student";

            Person person4 = new Person { Name = name4, Company = company4, Position = position4 };

            group3.AddPerson(person4);

            Assert.AreEqual(1, group3.Amount);

            string name5 = "mai";
            string company5 = "ynu";
            string position5 = "graduate";

            Person person5 = new Person { Name = name5, Company = company5, Position = position5 };

            group3.AddPerson(person5);

            contacts.AddGroup(group1);
            contacts.AddGroup(group2);
            contacts.AddGroup(group3);

            List<Group> groups = contacts.GetGroups();

            Assert.IsNotNull(groups);
            Assert.AreEqual(4, groups.Count);
        }
        
        [TestMethod]
        public void ContactsSearchGroup()
        {
            Contacts contacts = new Contacts();

            string name1 ="family";
            string name2 ="work";
            string name3 ="other";

            Group group1 = new Group() { Name = name1 };
            Group group2 = new Group() { Name = name2 };
            Group group3 = new Group() { Name = name3 };

            contacts.AddGroup(group1);
            contacts.AddGroup(group2);
            contacts.AddGroup(group3);

            var res = contacts.SearchGroup("work");

            Assert.AreEqual(1, res.Count);
        }
        
        [TestMethod]
        public void ContactsSearchPerson()
        {
            Contacts contacts = new Contacts();

            Group group1 = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group1.AddPerson(person1);

            Assert.AreEqual(1, group1.Amount);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group1.AddPerson(person2);

            Group group2 = new Group();

            string name3 = "chao";
            string company3 = "ynu";
            string position3 = "graduate";

            Person person3 = new Person { Name = name3, Company = company3, Position = position3 };

            group2.AddPerson(person3);

            Group group3 = new Group();

            string name4 = "maichao";
            string company4 = "ynu";
            string position4 = "student";

            Person person4 = new Person { Name = name4, Company = company4, Position = position4 };

            group3.AddPerson(person4);

            Assert.AreEqual(1, group3.Amount);

            string name5 = "mai";
            string company5 = "ynu";
            string position5 = "graduate";

            Person person5 = new Person { Name = name5, Company = company5, Position = position5 };

            group3.AddPerson(person5);

            string name = "maimai";
            string company = "ynu";
            string position = "graduate";

            Person person = new Person { Name = name, Company = company, Position = position };

            group1.AddPerson(person);
            group2.AddPerson(person);
            group3.AddPerson(person);

            contacts.AddGroup(group1);
            contacts.AddGroup(group2);
            contacts.AddGroup(group3);

            var res1 = contacts.SearchPerson("ynu");
            var res2 = contacts.SearchPerson("mai");
            var res3 = contacts.SearchPerson("maimai");
        }
    }
}
