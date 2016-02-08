using System;
using System.Text;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Domain;
using Infrastructure;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace UnitTests
{
    /// <summary>
    /// UnitTestBinaryDataAccess 的摘要说明
    /// </summary>
    [TestClass]
    public class UnitTestBinaryDataAccess
    {
        public UnitTestBinaryDataAccess()
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
        public void SaveData()
        {
            //Contacts1 contacts1 = new Contacts1() { Name = "waef" };

            //FileStream fileStream = new FileStream("data.dat", FileMode.Create, FileAccess.Write);
            //BinaryFormatter binaryFormatter = new BinaryFormatter();
            //binaryFormatter.Serialize(fileStream, contacts1);

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

            FileStream fileStream = new FileStream("data.dat", FileMode.Create, FileAccess.Write);
            BinaryFormatter binaryFormatter = new BinaryFormatter();
            binaryFormatter.Serialize(fileStream, person1);
            //BinaryDataAccess bda = new BinaryDataAccess();
            //bda.SaveData(contacts, "data.dat");
        }

        [TestMethod]
        public void LoadData()
        {
            //FileStream fileStream = new FileStream("data.dat", FileMode.Open, FileAccess.Read);
            //BinaryFormatter binaryFormatter = new BinaryFormatter();
            //Contacts1 res = binaryFormatter.Deserialize(fileStream) as Contacts1;
        }
    }

    //[Serializable]
    //class Person1
    //{
    //    public Guid Id { set; get; }
    //    public string Name { set; get; }
    //    public string Company { set; get; }
    //    public string Position { set; get; }
    //    public string Notes { set; get; }
    //    public List<Pair<Guid, Pair<string, string>>> Phones { set; get; }
    //}

    //[Serializable]
    //class Group1
    //{
    //    public string Name { set; get; }
    //    public List<Person1> persons { set; get; }
    //}

    //[Serializable]
    //class Contacts1
    //{
    //    public string Name { set; get; }
    //    public List<Group1> persons { set; get; }
    //}
}
