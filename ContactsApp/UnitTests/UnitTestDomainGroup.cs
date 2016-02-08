using System;
using System.Text;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Domain;

namespace UnitTests
{
    /// <summary>
    /// UnitTestDomainGroup 的摘要说明
    /// </summary>
    [TestClass]
    public class UnitTestDomainGroup
    {
        public UnitTestDomainGroup()
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
        public void GroupNew()
        {
            string name = "family";

            Group group = new Group();

            Assert.IsNotNull(group.Id);
            Assert.AreEqual(0, group.Amount);

            group.Name = name;
            Assert.AreEqual(name, group.Name);
        }

        [TestMethod]
        public void GroupAdd()
        {
            Group group = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group.AddPerson(person1);

            Assert.AreEqual(1, group.Amount);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group.AddPerson(person2);

            Assert.AreEqual(2, group.Amount);

            Assert.AreNotEqual(group.Persons[0], group.Persons[1]);
        }

        [TestMethod]
        public void GroupDelete()
        {
            Group group = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group.AddPerson(person1);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group.AddPerson(person2);

            group.DeletePerson(group.Persons[0]);

            Assert.AreEqual(1, group.Amount);
            Assert.AreEqual(name2, group.Persons[0].Name);
        }

        [TestMethod]
        public void GroupSearchPersonById()
        {
            Group group = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group.AddPerson(person1);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group.AddPerson(person2);

            Person person = group.SearchPersonById(person1.Id);

            Assert.IsNotNull(person);
            Assert.AreEqual(person1.Id, person.Id);
            Assert.AreEqual(name1, person.Name);
            Assert.AreEqual(company1, person.Company);
            Assert.AreEqual(position1, person.Position);
        }

        [TestMethod]
        public void GroupGetPersons()
        {
            Group group = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group.AddPerson(person1);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group.AddPerson(person2);

            List<Person> persons = group.Persons;

            Assert.IsNotNull(persons);
            Assert.AreEqual(2, group.Amount);
        }

        [TestMethod]
        public void GroupSearchPerson()
        {
            Group group = new Group();

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            group.AddPerson(person1);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group.AddPerson(person2);

            string name3 = "chao";
            string company3 = "ynu";
            string position3 = "ynu";

            Person person3 = new Person { Name = name3, Company = company3, Position = position3 };

            group.AddPerson(person3);

            var ans1 = group.SearchPerson("mai");

            Assert.IsNotNull(ans1);
            Assert.AreEqual(1, ans1.Count);

            var ans2 = group.SearchPerson("ynu");

            Assert.IsNotNull(ans2);
            Assert.AreEqual(3, ans2.Count);
        }
    }
}
