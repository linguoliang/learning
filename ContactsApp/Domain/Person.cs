using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Domain
{
    [Serializable]
    public class Person
    {
        public Guid Id { set; get; }
        public string Name { set; get; }
        public string Company { set; get; }
        public string Position { set; get; }
        public string Notes { set; get; }

        /// <summary>
        /// guid, number and type
        /// </summary>
        public List<Pair<Guid, Pair<string, string>>> Phones { set; get; }

        /// <summary>
        /// guid, email and type
        /// </summary>
        public List<Pair<Guid, Pair<string, string>>> Emails { set; get; }

        /// <summary>
        /// guid, address and type
        /// </summary>
        public List<Pair<Guid, Pair<string, string>>> Addresses { set; get; }

        /// <summary>
        /// guid, date and type
        /// </summary>
        public List<Pair<Guid, Pair<string, string>>> Dates { set; get; }

        public Person()
        {
            Id = Guid.NewGuid();
            Phones = new List<Pair<Guid, Pair<string, string>>>();
            Emails = new List<Pair<Guid, Pair<string, string>>>();
            Addresses = new List<Pair<Guid, Pair<string, string>>>();
            Dates = new List<Pair<Guid, Pair<string, string>>>();
        }

        public void UpdateInfo(Person person)
        {
            Type t = typeof(Person);
            var properties = t.GetProperties();

            foreach (var item in properties)
            {
                item.SetValue(this, item.GetValue(person));
            }
        }

        public void AddPhone(Pair<Guid, Pair<string, string>> phone)
        {
            Phones.Add(phone);
        }

        public void DeletePhoneById(Guid id)
        {
            Phones.Remove(this.SearchPhoneById(id));
        }

        public Pair<Guid, Pair<string, string>> SearchPhoneById(Guid id)
        {
            return Phones.Find(phone => new Guid(phone.Key.ToString()) == id);
        }

        public void AddEmail(Pair<Guid, Pair<string, string>> email)
        {
            Emails.Add(email);
        }

        public void DeleteEmailById(Guid id)
        {
            Emails.Remove(this.SearchEmailById(id));
        }

        public Pair<Guid, Pair<string, string>> SearchEmailById(Guid id)
        {
            return Emails.Find(email => new Guid(email.Key.ToString()) == id);
        }

        public void AddAddress(Pair<Guid, Pair<string, string>> address)
        {
            Addresses.Add(address);
        }

        public void DeleteAddressById(Guid id)
        {
            Addresses.Remove(this.SearchAddressById(id));
        }

        public Pair<Guid, Pair<string, string>> SearchAddressById(Guid id)
        {
            return Addresses.Find(address => new Guid(address.Key.ToString()) == id);
        }

        public void AddDate(Pair<Guid, Pair<string, string>> date)
        {
            Dates.Add(date);
        }

        public void DeleteDateById(Guid id)
        {
            Dates.Remove(this.SearchDateById(id));
        }

        public Pair<Guid, Pair<string, string>> SearchDateById(Guid id)
        {
            return Dates.Find(date => new Guid(date.Key.ToString()) == id);
        }

        public bool isGUIDExist(string id)
        {
            Type t = typeof(Person);
            var properties = t.GetProperties();

            foreach (PropertyInfo property in properties)
            {
                if (property.PropertyType.IsGenericType)
                {
                    var p = property.GetValue(this) as List<Pair<Guid, Pair<string, string>>>;

                    foreach (var item in p)
                    {
                        if (item.Key.ToString() == id)
                        {
                            return true;
                        }
                    }
                }
            }

            return false;
        }
    }
}
