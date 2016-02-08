using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Domain
{
    [Serializable]
    public class Contacts
    {
        public int GroupsAmount
        {
            get
            {
                return groups.Count;
            }
        }

        public int PersonsAmount
        {
            get
            {
                int personsAmount = 0;

                foreach (var group in groups)
                {
                    personsAmount += group.Amount;
                }

                return personsAmount;
            }
        }

        private List<Group> groups;

        public Contacts()
        {
            groups = new List<Group>();
            Group group = new Group() { Name = "Default" };
            this.AddGroup(group);
        }

        public void AddPerson(Person person)
        {
            // add to Default group
            this.SearchGroup("Default")[0].AddPerson(person);
        }

        public void DeletePerson(Person person)
        {
            foreach (var group in groups)
            {
                if (group.SearchPersonById(person.Id) != null)
                {
                    group.DeletePerson(person);
                }
            }
        }

        public void UpdatePerson(Person person)
        {
            foreach (var group in groups)
            {
                if (group.SearchPersonById(person.Id) != null)
                {
                    group.UpdatePerson(person);
                }
            }
        }

        public void MovePersonToGroup(Person person, Group curGroup, Group newGroup)
        {
            this.SearchGroupById(newGroup.Id).AddPerson(person);
            this.SearchGroupById(curGroup.Id).DeletePerson(person);
        }

        public void AddPersonToGroup(Person person, Group group)
        {
            this.SearchGroupById(group.Id).AddPerson(person);
        }

        public void AddGroup(Group group)
        {
            groups.Add(group);
        }

        public void DeleteGroup(Group group)
        {
            Group groupDefault = this.SearchGroup("Default")[0];

            // move its contacts to default group
            foreach (Person person in group.Persons)
            {
                groupDefault.AddPerson(person);
            }

            // delete it
            groups.Remove(this.SearchGroupById(group.Id));
        }

        public void UpdateGroup(Group group)
        {
            this.SearchGroupById(group.Id).UpdateInfo(group);
        }

        public Group SearchGroupById(Guid id)
        {
            return groups.Find(group => group.Id == id);
        }

        public List<Group> SearchGroup(string condition)
        {
            List<Group> res = new List<Group>();

            foreach (var group in groups)
            {
                Type t = typeof(Group);

                var properties = t.GetProperties();

                foreach (var property in properties)
                {
                    object value = property.GetValue(group);

                    if (value != null && value.ToString() == condition && !res.Contains(group))
                    {
                        res.Add(group);
                    }
                }
            }

            return res;
        }

        public List<Group> SearchPerson(string condition)
        {
            List<Group> resGroup = new List<Group>();

            foreach (var group in groups)
            {
                Group g = new Group() { Name = group.Name };
                var persons = group.Persons;

                foreach (var person in persons)
                {
                    Type t = typeof(Person);

                    var properties = t.GetProperties();

                    foreach (var property in properties)
                    {
                        object value = property.GetValue(person);

                        if (value != null && value.ToString() == condition)
                        {
                            if (!resGroup.Contains(g))
                            {
                                resGroup.Add(g);
                            }

                            if (!g.Persons.Contains(person))
                            {
                                g.AddPerson(person);
                            }
                        }
                    }
                }
            }

            return resGroup;
        }

        public List<Group> GetGroups()
        {
            return groups;
        }
    }
}
