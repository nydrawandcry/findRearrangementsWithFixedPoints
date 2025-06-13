/*!
* \file
* \brief Данный файл содержит тесты для функции splitString.
*/

#include "pch.h"
#include "CppUnitTest.h"
#include "../findRearrangementsWithFixedPoints/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			/*!
			* \brief Преобразует std::vector<std::string> в std::wstring для корректного отображения в тестах.
			* \param [in] vec - Вектор строк, который нужно отобразить.
			* \return Строковое представление вектора в формате { "str1", "str2", ... }.
			*/
			static wstring ToString(const vector<string>& vec)
			{
				wstringstream ss;
				ss << L"{";
				for (size_t i = 0; i < vec.size(); ++i)
				{
					ss << L"\"" << wstring(vec[i].begin(), vec[i].end()) << L"\"";
					if (i < vec.size() - 1)
						ss << L", ";
				}
				ss << L"}";
				return ss.str();
			}
		}
	}
}

namespace testsplitString
{
	/*!
	* \class testsplitString
	* \brief Набор модульных тестов для функции splitString.
	*/
	TEST_CLASS(testsplitString)
	{
	public:
		
		/*!
		* \brief Проверяет корректную обработку пустой строки.
		*/
		TEST_METHOD(EmptyStr)
		{
			string input_str = "";
			vector<string> expected_str(0);

			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}

		/*!
		* \brief Проверяет, что строка, состоящая только из букв, возвращается как один токен.
		*/
		TEST_METHOD(LettersOnly)
		{
			string input_str = "aaabbbccc";
			vector<string> expected_str =
			{
				"aaabbbccc"
			};
			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}

		/*!
		* \brief Проверяет, что строка, состоящая только из цифр, возвращается как один токен.
		*/
		TEST_METHOD(NumbersOnly)
		{
			string input_str = "17569";
			vector<string> expected_str =
			{
				"17569"
			};
			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}

		/*!
		* \brief Проверяет, что функция корректно обрабатывает пробелы.
		*/
		TEST_METHOD(CorrectSeparators)
		{
			string input_str = " f f ";
			vector<string> expected_str =
			{
				"f", "f"
			};
			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}

		/*!
		* \brief Проверяет, что функция корректно обрабатывает разделители различного вида.
		*/
		TEST_METHOD(IncorrectSeparators)
		{
			string input_str = "\t-_;:?";
			vector<string> expected_str =
			{
				"-", "_", ";", ":", "?"
			};
			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}

		/*!
		* \brief Проверяет, что функция обрабатывает буквы разных регистров.
		*/
		TEST_METHOD(HighCase)
		{
			string input_str = "AdSghD";
			vector<string> expected_str =
			{
				"AdSghD"
			};
			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}

		/*!
		* \brief Проверяет, что функция корректно обрабатывает строку с правильно введенными входными данными.
		*/
		TEST_METHOD(CorrectInput)
		{
			string input_str = "n=5, k=3";
			vector<string> expected_str =
			{
				"n", "=", "5", ",", "k", "=", "3"
			};

			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}

		/*!
		* \brief Проверяет, что функция корректно выделяет подстроку, являющейся двузначным целым числом.
		*/
		TEST_METHOD(TwoDigitNumber)
		{
			string input_str = "n=9, k=20";
			vector<string> expected_str =
			{
				"n", "=", "9", ",", "k", "=", "20"
			};
			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}

		/*!
		* \brief Проверяет, что функция корректно разделяет строку со специальными символами.
		*/
		TEST_METHOD(SpecialCharactersInInput)
		{
			string input_str = "n#=5, k=0";
			vector<string> expected_str =
			{
				"n", "#", "=", "5", ",", "k", "=", "0"
			};
			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}

		/*!
		* \brief Комплексный тест с разными видами проверок.
		*/
		TEST_METHOD(ComplexTest)
		{
			string input_str = "n_2=32, k=@43";
			vector<string> expected_str =
			{
				"n", "_", "2", "=", "32", ",", "k", "=", "@", "43"
			};
			vector<string> splited_str = splitString(input_str);

			Assert::AreEqual(expected_str, splited_str);
		}
	};
}
