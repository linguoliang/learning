using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Windows;
using Domain;

namespace Infrastructure
{
    public class BinaryDataAccess : IDataAccess
    {
        public void SaveData(string fileName, Object obj)
        {
            FileStream fileStream = new FileStream(fileName, FileMode.Create, FileAccess.Write);
            BinaryFormatter binaryFormatter = new BinaryFormatter();
            binaryFormatter.Serialize(fileStream, obj);
        }

        public Contacts LoadData(string fileName)
        {
            FileStream fileStream = new FileStream(fileName, FileMode.Open, FileAccess.Read);
            BinaryFormatter binaryFormatter = new BinaryFormatter();
            return binaryFormatter.Deserialize(fileStream) as Contacts;
        }
    }
}
