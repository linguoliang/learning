using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Domain
{
    [Serializable]
    public class Group
    {
        public Guid Id { set; get; }
        public string Name { set; get; }
        public int Amount
        {
            get
            {
                return Persons.Count;
            }
        }
        public List<Person> Persons { set; get; }

        public Group()
        {
            Id = Guid.NewGuid();
            Persons = new List<Person>();
        }

        public void UpdateInfo(Group group)
        {
            this.Name = group.Name;
        }

        public void AddPerson(Person person)
        {
            Persons.Add(person);
        }

        public void UpdatePerson(Person person)
        {
            this.SearchPersonById(person.Id).UpdateInfo(person);
        }

        public void DeletePerson(Person person)
        {
            Persons.Remove(this.SearchPersonById(person.Id));
        }

        public Person SearchPersonById(Guid id)
        {
            return Persons.Find(person => person.Id == id);
        }

        public List<Person> SearchPerson(string condition)
        {
            List<Person> res = new List<Person>();

            foreach (Person person in Persons)
            {
                Type t = typeof(Person);

                var properties = t.GetProperties();

                foreach (PropertyInfo property in properties)
                {
                    object value = property.GetValue(person);

                    if (value != null && value.ToString() == condition && !res.Contains(person))
                    {
                        res.Add(person);
                    }
                }
            }

            return res;
        }
    }
}
