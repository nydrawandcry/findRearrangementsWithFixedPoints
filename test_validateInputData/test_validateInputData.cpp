#include "pch.h"
#include "CppUnitTest.h"
#include "../findRearrangementsWithFixedPoints/functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
