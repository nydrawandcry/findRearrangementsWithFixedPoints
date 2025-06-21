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

			template<>
			/*!
			* \brief Преобразует DataErrors в std::wstring для корректного отображения в тестах.
			* \param [in] e - тип ошибки, которую нужно отобразить.
			* \return Строковое представление ошибки.
			*/
			static std::wstring ToString<DataErrors>(const DataErrors& e)
			{
				switch (e)
				{
				case NO_DATA_ERROR:
					return L"NO_DATA_ERROR";
				case TOO_MANY_SYMBOLS:
					return L"WRONG_SYMBOL_COUNT";
				case NO_INT:
					return L"NO_INT";
				case WRONG_INPUT:
					return L"WRONG_INPUT";
				default:
					return L"UNKNOWN_ERROR";
				}
			}
		}
	}
}
namespace testvalidateInputData
{
	TEST_CLASS(testvalidateInputData)
	{
	public:
		
		TEST_METHOD(CorrectInput)
		{
			string input_string = "n=5, k=2";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = NO_DATA_ERROR;

			Assert::AreEqual(exp_errortype, errortype);
		}

		TEST_METHOD(WrongSymbolsCount)
		{
			string input_string = "n=5, k=";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = TOO_MANY_SYMBOLS;

			Assert::AreEqual(exp_errortype, errortype);
		}

		TEST_METHOD(ParametersAreNotInt)
		{
			string input_string = "n=a, k=e";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = NO_INT;

			Assert::AreEqual(exp_errortype, errortype);
		}

		TEST_METHOD(ParametersAreEmpty)
		{
			string input_string = "n= , k= ";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = TOO_MANY_SYMBOLS;

			Assert::AreEqual(exp_errortype, errortype);
		}

		TEST_METHOD(WrongParametersNames)
		{
			string input_string = "a=5, b=7";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = WRONG_INPUT;

			Assert::AreEqual(exp_errortype, errortype);
		}

		TEST_METHOD(ManySeparators)
		{
			string input_string = "n==5, k=2";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = TOO_MANY_SYMBOLS;

			Assert::AreEqual(exp_errortype, errortype);
		}

		TEST_METHOD(SpecialSymbolsInStr)
		{
			string input_string = "n_=5, k=2";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = TOO_MANY_SYMBOLS;

			Assert::AreEqual(exp_errortype, errortype);
		}

		TEST_METHOD(WrongParametersNamesRegister)
		{
			string input_string = "N=5, K=2";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = WRONG_INPUT;

			Assert::AreEqual(exp_errortype, errortype);
		}

		TEST_METHOD(ManyWhiteSeparators)
		{
			string input_string = "n=5,\tk=2    ";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = NO_DATA_ERROR;

			Assert::AreEqual(exp_errortype, errortype);
		}

		TEST_METHOD(ComplexTest)
		{
			string input_string = "N=5, k=a";
			vector<string> string_elements = {};

			DataErrors errortype = validateInputData(input_string, string_elements);
			DataErrors exp_errortype = WRONG_INPUT;

			Assert::AreEqual(exp_errortype, errortype);
		}
	};
}
