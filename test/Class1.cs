using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary2Z
{
    public class PasswordChecker
    {
        public static bool validatePassword(string password)
        {
            if (password.Length < 8 || password.Length > 20)
                return false;
            if (!password.Any(Char.IsDigit))
                return false;
            if (!password.Any(Char.IsUpper))
                return false;
            if (!password.Any(Char.IsLower))
                return false;
            if (password.Intersect("#$%^&_)").Count() == 0)
                return false;
            return true;
        }

        public static void Main(string[] args)
        {
            bool arr = PasswordChecker.validatePassword("1)Kghbdtn");

            Console.WriteLine("res = " + arr);

            Console.ReadKey();
        }
    }
}
