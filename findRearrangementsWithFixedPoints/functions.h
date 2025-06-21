/*!
* \file
* \brief Данный файл содержит заголовки функций для работы программы findRearrangementsWithFixedPoints.
*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

/*!
* \brief Перечисление типов ошибок, которые могут возникнуть с входными данными
*/
enum DataErrors
{
    NO_DATA_ERROR, //!< ошибок с данными нет

    WRONG_SYMBOL_COUNT, //!< неправильное количество элементов строки, что не соответствует шаблону

    WRONG_INPUT, //!< несоответствие строки нужному шаблону

    NO_INT //!< в нужных элементах строки не целочисленные значения
};

/*!
* \brief Функция для считывания данных из входного файла
* \param [in] - input_file_path - абсолютный или относительный путь к входному файлу
* \param [in] - params - параметры, считанные из входного файла
* \return true - данные удалось считать
* \return false - данные не удалось считать
*/
bool readFile(ifstream& input_file, vector<string>& file_content);

/*!
* \brief Функция, которая разбивает строку на подстроки по пробелам или другим разделителям
* \param [in] input_data - строка, которую необходимо разбить на символы
* \return контейнер с символами, на которые была разбита строка
*/
vector<string> splitString(string& input_string);

/*!
* \brief Функция, проверяющая элемент строки, является ли он целым числом
* \param [in] str - проверяемый элемент
* \return true - элемент является числом
* \return false - элемент не является числом
*/
bool isInt(const string& str);

/*!
* \brief Функция, обрабатывающая строку с входными данными
* \param [in] input_string - строка, которую мы проверяем на корректность
* \param [in] string_elements - символы и слова строки для проверки на корректность
* \return true - данные введены корректно
* \return false - данные введены некорректно
*/
DataErrors validateInputData(string& input_string, vector<string>& string_elements);

/*!
* \brief Функция, проверяющая результат валидации входной строки с параметрами
* \param [in] error - тип ошибки валидации входной строки
* \param [in] splited_string - входная строка, обработанная для валидации
* \return true - строка соответствует условиям ввода
* \return false - строка не соответствует условиям ввода
*/
bool checkValidationResult(DataErrors error, const vector<string>& splited_string);

/*!
* \brief Функция, находящая всевозможные перестановки с неподвижными точками заданного размера и количества соответственно
* \param [in] current_permutation - текущая перестановка которую мы собираем
* \param [in] index - позиция элемента которую мы рассматриваем на текущий момент
* \param [in] used_elements - контейнер с уже использованными числами
* \param [in] max_fixed_points - максимум неподвижных точек которые могут быть в перестановке
* \param [in] fixed_points_count - счетчик неподвижных точек в перестановке
* \param [in] generated_permutations - контейнер с уже сгенерированными перестановками, который мы постоянно будем пополнять с каждым вызовом рекурсии
*/
void generateRearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations);

/*!
* \brief Функция для записи данных в выходной файл
* \param [in] generated_permutations - все сгенерированные перестановки, которые нужно записать в выходной файл
* \param [in] output_file - выходной файл, в которые записываются данные
*/
void recOutputFile(vector<vector<int>>& generated_permutations, ofstream& output_file);