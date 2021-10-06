using Microsoft.VisualStudio.TestTools.UnitTesting;
using ClassLibrary2Z;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary2Z.Tests
{
    [TestClass()]
    public class PasswordCheckerTests
    {
        
        [TestMethod()]
        public void Check_8Symbols_ReturnsTrue()
        {
            // Arrange - устанавливает начальные условия для выполнения теста
            // Объявляем переменную для установки пароля из тестовых данных
            // Объявляем ожидаемое значение в результате выполнения теста
            // берем из тестовых данных
            string password = "WSDllf582$";
            bool expected = true; 
            // Act - выполняем сам тест
            // В блоке Act создаем переменную, которая вернет актуальный результат при выполнении метода 
            // CheckPassword. В нашем случае ValidatePassword
            bool actual = PasswordChecker.validatePassword(password); 
            // Assert - верифицирует результат теста, и, в данном случае, оформление-повышает читаемость текста и облегчает его использование в качестве документации к текстируемой функциональности
            // С помощью класса Assert сравниваем два значения ожидаемое и реальное, метод AreEquel, и в качестве аргумента-наши данные
            Assert.AreEqual(expected,actual); 
        }
        [TestMethod()]
        public void Check_20Symbols_ReturnsFalse()
        {
            string password = "KDSFFDSGDSGSJKSGJKSGKGSSG";

            bool actual = PasswordChecker.validatePassword(password);
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_4Symbols_ReturnsFalse()
        {
            string password = "Aq1$";
            
            bool actual = PasswordChecker.validatePassword(password);
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_digit_ReturnsTrue()
        {
            // Arrange
            string password = "GGffwqzf23!";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void Check_Nodigit_ReturnsTrue()
        {
            // Arrange
            string password = "GGffwqzf!";
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_SpecialSymbols_ReturnsTrue()
        {
            // Arrange
            string password = "FfgKJH992!";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void Check_ConventionalLetters_ReturnsTrue()
        {
            // Arrange
            string password = "sSAF9CGJ#";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void Check_LowercaseLetters_ReturnsFalse()
        {
            // Arrange
            string password = "K4455553!";
            
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_Lowercase_ReturnsTrue()
        {
            // Arrange
            string password = "Mmm9gfj#";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }
        [TestMethod()]
        public void Check_ConventionalLetters_ReturnsFalse()
        {
            // Arrange
            string password = "k4455553!";
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.IsFalse(actual);
        }
        [TestMethod()]
        public void Check_CorrectPassword_ReturnsTrue()
        {
            // Arrange
            string password = "WSDllf582$";
            bool expected = true;
            // Act
            bool actual = PasswordChecker.validatePassword(password);
            // Assert
            Assert.AreEqual(expected, actual);
        }

    }
}
