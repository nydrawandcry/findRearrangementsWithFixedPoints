/*!
* \file
* \brief Данный файл содержит в себе реализацию функций, которые используются в ходе работы программы findRearrangementsWithFixedPoints.
*/

#include <vector>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

/*!
 * \details Читает построчно данные из файла
 */
bool readFile(ifstream& input_file, vector<string>& file_content)
{
    string input_line;

    //считываем построчно данные из файла до коцна файла
    while (getline(input_file, input_line))
    {
        file_content.push_back(input_line);
    }

    //после считывания закрываем файл
    input_file.close();

    //проверка, удалось ли загрузить данные из файла
    if (!file_content.empty())
    {
        return true;
    }

    //если не получилось считать данные, возвращаем "неудачу" о записи файла
    return false;
}

/*!
 * \details Разбивает строку на подстроки: целые числа, символы и разделители, предусмотренные условием оформления входных данных(',', ' ', '=').
 */
vector<string> splitString(string& input_string)
{
    vector<string> splited_string;
    string current_symbol;

    //для всей строки
    for (char c : input_string)
    {
        //если символ число или буква
        if (isalnum(c))
        {
            //начинаем выделять отдельный элемент строки
            current_symbol += c;
        }
        //если символ не число или буква
        if (!isalnum(c))
        {
            //если уже начали выделять отдельный элемент строки
            if (!current_symbol.empty())
            {
                //добавляем отделенный элемент строки в контейнер с разделенными элементами 
                    // и очищаем текущий отделенный элемент для следующего отделения нового элемента
                splited_string.push_back(current_symbol);
                current_symbol.clear();
            }
            //если перед нами белый разделитель (табуляция или пробел)
            if (c != ' ' && c != '\t')
            {
                //добавляем отделенный элемент строки в контейнер с разделенными элементами и пропускаем белые разделители
                splited_string.push_back(string(1, c));
            }
        }
    }

    //если после обхода всей строки еще остался отделенный элемент строки
    if (!current_symbol.empty())
    {
        //добавляем последний элемент
        splited_string.push_back(current_symbol);
    }

    //возвращаем контейнер со всеми разделенными элементами строки
    return splited_string;
}

/*!
* \detailes Проверяет определенно расположенные элементы строки на то, являются ли они целыми числами
*/
bool isInt(const string& str)
{
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

/*!
 * \details Проверяет строку на соответствие шаблону: n=<целое число>, k=<целое число>.
 */
DataErrors validateInputData(string& input_string, vector<string>& string_elements)
{
    //необходимо разбить строку на смиволы, слова и корректные разделители
    string_elements = splitString(input_string);

    //если количество элементов строки некорректно (должно быть равно 7)
    if (string_elements.size() != 7)
    {
        return TOO_MANY_SYMBOLS;
    }

    //если строка не соответствует шаблону ввода
    if (string_elements[0] != "n" || string_elements[1] != "=" || string_elements[3] != "," || string_elements[4] != "k" || string_elements[5] != "=")
    {
        return WRONG_INPUT;
    }

    if (!isInt(string_elements[2]) || !isInt(string_elements[6]))
    {
        return NO_INT;
    }

    //если все хорошо, считаем, что строка обработана успешно и всё корректно
    return NO_DATA_ERROR;
}

/*!
* \details Проверяет результат работы функции validateInputData на все предусмотренные типы ошибок и при ошибке выводит её в консоль
*/
bool checkValidationResult(DataErrors error, const vector<string>& splited_string)
{
    switch (error) 
    {
    case TOO_MANY_SYMBOLS:

        cerr << "Ожидаемое количество элементов: 7. Получено: " << splited_string.size() << '\n';
        return false;

    case WRONG_INPUT:

        cerr << "Строка не соответствует шаблону \"n = <число>, k = <число>\".\n";
        return false;

    case NO_INT:

        cerr << "Значения не являются целыми числами.\n";
        return false;

    default:

        return true;
    }
}

/*!
 * \details Рекурсивно генерирует все допустимые перестановки заданного размера с заданным числом неподвижных точек.
 */
void generateRearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations)
{
    //Если перестановка уже полностью заполнена и в ней присутствует заданное количество неподвижных точек
    if (index == current_permutation.size())
    {
        if (max_fixed_points == fixed_points_count)
        {
            //Добавить сгенерированную перестановку в контейнер с перестановками и начать генерацию новой перестановки
            generated_permutations.push_back(current_permutation);
            return;
        }
    }
    //Для каждого элемента перестановки
    for (int i = 0; i < current_permutation.size(); ++i)
    {
        //Если элемент уже использованный, не заносим его в перестановку
        if (used_elements[i])
        {
            continue;
        }

        bool is_fixed = (i == index);

        //Иначе если все неподвижные точки уже проставлены, и текущий элемент является неподвижной точкой, не заносим его в перестановку
        if (is_fixed && max_fixed_points == fixed_points_count)
        {
            continue;
        }

        //Иначе если подвижная точка стоит на своем месте (является неподвижной и противоречит условию генерации), не заносим его в перестановку
        if (is_fixed && fixed_points_count >= max_fixed_points)
        {
            continue;
        }

        //Иначе Если текущий элемент подходит для перестановки, вставляем элемент в нее
        used_elements[i] = true;
        current_permutation[index] = i + 1;

        //Вызов рекурсии
        generateRearrangements(current_permutation, index + 1, used_elements, max_fixed_points, fixed_points_count + (is_fixed ? 1 : 0), generated_permutations);

        //Откат для обхода и новых вариантов перестановки
        used_elements[i] = false;
    }

}

/*!
 * \details Выводит все сгенерованные перестановки в выходной файл по шаблону: [n1, n2... n](перестановка) - k1, k2, ... k (неподвижные точки) или no fixed points(отсутствие неподвижных точек).
 */
void recOutputFile(vector<vector<int>>& generated_permutations, ofstream& output_file)
{
    //вывести количество сгенерированных перестановок в файл
    output_file << generated_permutations.size() << endl;

    //для всех сгенерированных перестановок
    for (const auto& output_permutation : generated_permutations)
    {
        //начало вывода перестановки: вывод открывающей квадратной скобки "["
        output_file << "[";

        //вывод элементов перестановки через запятую
        for (size_t i = 0; i < output_permutation.size(); ++i)
        {
            if (i != 0)
            {
                output_file << ", ";
            }

            output_file << output_permutation[i];
        }

        //при окончании вывода перестановки закрываем скобки и ставим дефис для перечисления неподжвижных точек "] - "
        output_file << "] - ";

        //начинаем поиск всех неподвижных точек в выведенной перестановке
        vector<int> output_fixed_points;

        for (size_t i = 0; i < output_permutation.size(); ++i)
        {
            //если находим неподвижную точку 
            if (output_permutation[i] == static_cast<int>(i) + 1)
            {
                //добавляем ее в контейнер для неподвижных точек
                output_fixed_points.push_back(output_permutation[i]);
            }
        }

        //если неподвижных точек в перестановке нет (не нашли)
        if (output_fixed_points.empty())
        {
            //вывод "no fixed points" после выведенной перестановки
            output_file << "no fixed points";

            //начинаем вывод новой перестановки с новой строки
            output_file << endl;
        }
        //иначе
        else
        {
            //для всех неподвижных точек
            for (size_t i = 0; i < output_fixed_points.size(); ++i)
            {
                //выводим через запятую все неподвижные точки
                if (i != 0)
                {
                    output_file << ", ";
                }

                output_file << output_fixed_points[i];
            }

            //начинаем вывод новой перестановки с новой строки
            output_file << endl;
        }
    }
    //закрыть выходной файл
    output_file.close();
}