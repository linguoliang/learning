using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Domain;
using Infrastructure;

namespace Service
{
    public class Services
    {
        private Contacts contacts;

        public Services()
        {
            contacts = new Contacts();
            this.LoadContacts();
        }

        public void AddPerson(Person person)
        {
            contacts.AddPerson(person);
        }

        public void UpdatePerson(Person person)
        {
            contacts.UpdatePerson(person);
        }

        public void DeletePerson(Person person)
        {
            contacts.DeletePerson(person);
        }

        public List<Group> SearchPerson(string condition)
        {
            return contacts.SearchPerson(condition);
        }

        public void MovePersonToGroup(Person person, Group curGroup, Group newGroup)
        {
            contacts.MovePersonToGroup(person, curGroup, newGroup);
        }

        public void AddPersonToGroup(Person person, Group group)
        {
            contacts.AddPersonToGroup(person, group);
        }

        public void AddGroup(Group group)
        {
            contacts.AddGroup(group);
        }

        public void UpdateGroup(Group group)
        {
            contacts.UpdateGroup(group);
        }

        public void DeleteGroup(Group group)
        {
            contacts.DeleteGroup(group);
        }

        public List<Group> SearchGroup(string condition)
        {
            return contacts.SearchGroup(condition);
        }

        public Person SearchPersonById()
        {
            return null;
        }

        public Group SearchGroupById(string id)
        {
            return null;
        }

        public List<Group> GetGroups()
        {
            return contacts.GetGroups();
        }

        public void SaveContacts()
        {
            BinaryDataAccess bda = new BinaryDataAccess();
            bda.SaveData("data.dat", this.contacts);
        }

        public void LoadContacts()
        {
            //BinaryDataAccess bda = new BinaryDataAccess();
            //this.contacts = bda.LoadData("data.dat");

            Group group1 = new Group();
            group1.Name = "Family";

            string name1 = "maichao";
            string company1 = "ynu";
            string position1 = "student";

            Person person1 = new Person { Name = name1, Company = company1, Position = position1 };

            Pair<string, string> num1 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone1 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num1);

            person1.AddPhone(phone1);

            Pair<string, string> num2 = new Pair<string, string>("187", "cellphone");
            Pair<Guid, Pair<string, string>> phone2 = new Pair<Guid, Pair<string, string>>(Guid.NewGuid(), num2);

            person1.AddPhone(phone2);

            group1.AddPerson(person1);

            string name2 = "mai";
            string company2 = "ynu";
            string position2 = "graduate";

            Person person2 = new Person { Name = name2, Company = company2, Position = position2 };

            group1.AddPerson(person2);

            Group group2 = new Group();
            group2.Name = "Work";

            string name3 = "chao";
            string company3 = "ynu";
            string position3 = "graduate";

            Person person3 = new Person { Name = name3, Company = company3, Position = position3 };

            group2.AddPerson(person3);

            Group group3 = new Group();
            group3.Name = "Other";

            string name4 = "maichao";
            string company4 = "ynu";
            string position4 = "student";

            Person person4 = new Person { Name = name4, Company = company4, Position = position4 };

            group3.AddPerson(person4);

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
        }
    }
}
