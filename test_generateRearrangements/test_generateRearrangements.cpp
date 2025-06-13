/*!
* \file
* \brief Данный файл содержит тесты для функции generateRearrangements.
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
			* \brief Преобразует std::vector<std::vector<int>> в std::wstring для корректного отображения в тестах.
			* \param [in] vec - Вектор векторов целых чисел, который нужно отобразить.
			* \return Строковое представление вектора в формате { {int1, int2, ...}, {int1, int2, ...}, ... }.
			*/
			wstring ToString(const vector<vector<int>>& vec)
			{
				wstringstream ss;
				ss << L"{";

				for (size_t i = 0; i < vec.size(); ++i)
				{
					ss << L"{";
					for (size_t j = 0; j < vec[i].size(); ++j)
					{
						ss << vec[i][j];
						if (j < vec[i].size() - 1)
						{
							ss << L", ";
						}
					}
					ss << L"}";
					if (i < vec.size() - 1)
					{
						ss << L", ";
					}
				}
				ss << L"}";
				return ss.str();
			}

			template<>
			/*!
			* \brief Преобразует std::vector<int> в std::wstring для корректного отображения в тестах.
			* \param [in] vec - Вектор целых чисел, который нужно отобразить.
			* \return Строковое представление вектора в формате { int1, int2, ... }.
			*/
			static wstring ToString(const vector<int>& vec)
			{
				wstringstream ss;
				ss << L"{";
				for (size_t i = 0; i < vec.size(); ++i)
				{
					ss << vec[i];
					if (i < vec.size() - 1) ss << L", ";
				}
				ss << L"}";
				return ss.str();
			}
		}
	}
}

namespace testgenerateRearrangements
{
	/*!
	* \class testgenerateRearrangements
	* \brief Набор модульных тестов для функции generate_rearrangements.
	*/
	TEST_CLASS(testgenerateRearrangements)
	{
	public:

		/*!
		* \brief Проверяет функцию на генерацию перестановок с одной неподвижной точкой.
		*/
		TEST_METHOD(OneFixedPoint)
		{
			int n = 3;
			int max_fixed_points = 1;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			vector<vector<int>> expected_permutations =
			{
				{1, 3, 2},
				{2, 1, 3},
				{3, 2, 1}
			};

			Assert::AreEqual(generated_permutations, expected_permutations);
			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());

		}

		/*!
		* \brief Проверяет функцию на генерацию перестановок с двумя неподвижными точками.
		*/
		TEST_METHOD(SeveralFixedPoints)
		{
			int n = 5;
			int max_fixed_points = 2;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations =
			{
				{1, 2, 4, 5, 3},
				{1, 2, 5, 3, 4},
				{1, 3, 4, 2, 5},
				{1, 3, 5, 4, 2},
				{1, 4, 2, 3, 5},
				{1, 4, 3, 5, 2},
				{1, 5, 2, 4, 3},
				{1, 5, 3, 2, 4},
				{2, 3, 1, 4, 5},
				{2, 4, 3, 1, 5},
				{2, 5, 3, 4, 1},
				{3, 1, 2, 4, 5},
				{3, 2, 4, 1, 5},
				{3, 2, 5, 4, 1},
				{4, 1, 3, 2, 5},
				{4, 2, 1, 3, 5},
				{4, 2, 3, 5, 1},
				{5, 1, 3, 4, 2},
				{5, 2, 1, 4, 3},
				{5, 2, 3, 1, 4}
			};

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations, expected_permutations);
			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}

		/*!
		* \brief Проверяет функцию на генерацию перестановок с одной неподвижной точкой и средним количеством неподвижных точек.
		*/
		TEST_METHOD(SeveralElementsInThePermutation)
		{
			int n = 4;
			int max_fixed_points = 1;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations =
			{
				{1, 3, 4, 2},
				{1, 4, 2, 3},
				{2, 3, 1, 4},
				{2, 4, 3, 1},
				{3, 1, 2, 4},
				{3, 2, 4, 1},
				{4, 1, 3, 2},
				{4, 2, 1, 3}
			};

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations, expected_permutations);
			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}

		/*!
		* \brief Проверяет функцию на генерацию перестановок с максимально возможным количеством элементов в перестановке.
		*/
		TEST_METHOD(MaxElementsInThePerm)
		{
			int n = 9;
			int max_fixed_points = 5;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations(1134);

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}

		/*!
		* \brief Проверяет функцию на генерацию перестановок с максимально возможным количеством неподвижных точек.
		*/
		TEST_METHOD(OnePermutationCauseMaxFixedPts)
		{
			int n = 5;
			int max_fixed_points = 5;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations =
			{
				{1, 2, 3, 4, 5}
			};

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations, expected_permutations);
			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}

		/*!
		* \brief Проверяет функцию на генерацию одной перестановки(т.к. минимальное количество элементов)
		*/
		TEST_METHOD(OnePermutationCauseOneElementInThePerm)
		{
			int n = 1;
			int max_fixed_points = 1;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations =
			{
				{1}
			};

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations, expected_permutations);
			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}

		/*!
		* \brief Проверяет функцию на генерацию перестановок с количеством элементов перестановки, равным 6.
		*/
		TEST_METHOD(SeveralPermutations)
		{
			int n = 6;
			int max_fixed_points = 4;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations =
			{
				{1, 2, 3, 4, 6, 5},
				{1, 2, 3, 5, 4, 6},
				{1, 2, 3, 6, 5, 4},
				{1, 2, 4, 3, 5, 6},
				{1, 2, 5, 4, 3, 6},
				{1, 2, 6, 4, 5, 3},
				{1, 3, 2, 4, 5, 6},
				{1, 4, 3, 2, 5, 6},
				{1, 5, 3, 4, 2, 6},
				{1, 6, 3, 4, 5, 2},
				{2, 1, 3, 4, 5, 6},
				{3, 2, 1, 4, 5, 6},
				{4, 2, 3, 1, 5, 6},
				{5, 2, 3, 4, 1, 6},
				{6, 2, 3, 4, 5, 1}
			};

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations, expected_permutations);
			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}

		/*!
		* \brief Проверяет функцию на генерацию перестановок с максимально возможным количеством элементов перестановки и минимальном количеством неподвижных точек.
		*/
		TEST_METHOD(MaxPermutationsWithMaxElements)
		{
			int n = 9;
			int max_fixed_points = 0;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations(133496);

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}

		/*!
		* \brief Проверяет функцию на генерацию перестановок с количеством элементов перестановки, равным 2.
		*/
		TEST_METHOD(TwoElementsInPerm)
		{
			int n = 2;
			int max_fixed_points = 0;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations =
			{
				{2, 1}
			};

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations, expected_permutations);
			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}

		/*!
		* \brief Проверяет функцию на генерацию перестановок с количеством элементов перестановки, равным 7.
		*/
		TEST_METHOD(SevenElementsInPerm)
		{
			int n = 7;
			int max_fixed_points = 3;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations(315);

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}

		/*!
		* \brief Проверяет функцию на генерацию перестановок с количеством элементов перестановки, равным 8.
		*/
		TEST_METHOD(EightElementsInPerm)
		{
			int n = 8;
			int max_fixed_points = 2;

			vector<int> current_permutation(n);
			vector<bool> used_elements(n, false);
			int fixed_points_count = 0;
			vector<vector<int>> generated_permutations;

			vector<vector<int>> expected_permutations(7420);

			generateRearrangements(current_permutation, 0, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

			Assert::AreEqual(generated_permutations.size(), expected_permutations.size());
		}
	};
}
