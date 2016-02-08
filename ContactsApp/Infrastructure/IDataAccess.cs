using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Domain;

namespace Infrastructure
{
    interface IDataAccess
    {
        void SaveData(string fileName, Object obj);

        Contacts LoadData(string fileName);
    }
}
