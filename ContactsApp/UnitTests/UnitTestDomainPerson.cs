using System;
using System.Text;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Domain;
using Infrastructure;

namespace UnitTests
{
    /// <summary>
    /// UnitTestDomainPerson 的摘要说明
    /// </summary>
    [TestClass]
    public class UnitTestDomainPerson
    {
        public UnitTestDomainPerson()
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
        public void PersonNew()
        {
            string name = "maichao";
            string company = "ynu";
            string position = "student";

            Person person = new Person();

            Assert.IsNotNull(person.Id);

            person.Name = name;
            person.Company = company;
            person.Position = position;

            Assert.AreEqual(name, person.Name);
            Assert.AreEqual(company, person.Company);
            Assert.AreEqual(position, person.Position);
        }

        [TestMethod]
        public void PersonAddPhone()
        {
            string name = "maichao";
            string company = "ynu";
            string position = "student";

            Person person = new Person { Name = name, Company = company, Position = position };

            Pair<string, string> num1 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone1 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num1);

            person.AddPhone(phone1);

            Pair<string, string> num2 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone2 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num2);

            person.AddPhone(phone2);

            Assert.AreEqual(2, person.Phones.Count);
        }

        [TestMethod]
        public void PersonDeletePhone()
        {
            string name = "maichao";
            string company = "ynu";
            string position = "student";

            Person person = new Person { Name = name, Company = company, Position = position };

            Pair<string, string> num1 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone1 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num1);

            person.AddPhone(phone1);

            Pair<string, string> num2 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone2 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num2);

            person.AddPhone(phone2);

            person.DeletePhoneById(new Guid(phone1.Key.ToString()));

            Assert.AreEqual(1, person.Phones.Count);
        }

        [TestMethod]
        public void PersonSearchPhoneById()
        {
            string name = "maichao";
            string company = "ynu";
            string position = "student";

            Person person = new Person { Name = name, Company = company, Position = position };

            Pair<string, string> num1 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone1 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num1);

            person.AddPhone(phone1);

            Pair<string, string> num2 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone2 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num2);

            person.AddPhone(phone2);

            var phone = person.SearchPhoneById(new Guid(phone2.Key.ToString()));

            Assert.IsNotNull(phone);
            Assert.AreEqual(phone2.Key, phone.Key);
        }

        [TestMethod]
        public void PersonGetPhones()
        {
            string name = "maichao";
            string company = "ynu";
            string position = "student";

            Person person = new Person { Name = name, Company = company, Position = position };

            Pair<string, string> num1 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone1 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num1);

            person.AddPhone(phone1);

            Pair<string, string> num2 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone2 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num2);

            person.AddPhone(phone2);

            var phones = person.Phones;

            Assert.IsNotNull(phones);
        }
    }
}
