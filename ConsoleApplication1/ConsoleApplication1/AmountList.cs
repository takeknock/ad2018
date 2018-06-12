using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace ConsoleApplication1
{
    public class InternalAmount
    {
        public int A { get; set; }

        public double B { get; set; }
        public decimal C { get; set; }

    }

    public class AmountList : IEnumerable<InternalAmount>
    {
        IList<int> list1 = new List<int>{1,2,3};
        IList<double> list2 = new List<double> { 1.0, 2.0, 3.0 };
        IList<decimal> list3 = new List<decimal> { 1m, 2m, 3m };

        public IEnumerator<InternalAmount> GetEnumerator()
        {
            var ziped = list1.Zip(list2, (e1, e2) => new { e1, e2 }).Zip(list3, (e1e2, e3) => new InternalAmount {
                A = e1e2.e1,
                B = e1e2.e2,
                C = e3,
            });
            foreach(InternalAmount e in ziped)
            {
                yield return e;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }



        //public IEnumerable<InternalAmount> GetEnumerator()
        //{
        //    return GetEnumerator();
        //}


    }
}
