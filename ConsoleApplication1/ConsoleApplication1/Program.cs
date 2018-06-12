using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            AmountList l = new AmountList();
            var test = from e in l
                       select e;
                            
        }
    }
}
