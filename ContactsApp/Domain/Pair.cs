using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Domain
{
    public class Pair<T, U>
    {
        public Pair() { }

        public Pair(T key, U value)
        {
            this.Key = key;
            this.Value = value;
        }

        public T Key { get; set; }
        public U Value { get; set; }
    }
}
