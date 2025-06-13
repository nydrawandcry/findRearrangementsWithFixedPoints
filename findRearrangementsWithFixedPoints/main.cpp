/*!
* \file
* \brief Данный файл содержит главную функцию программы findRearrangementsWithFixedPoints.
*
* \mainpage Документация для программы "Find Rearrangements With Fixed Points (findRearrangementsWithFixedPoints)"
Программа предназначена для нахождения количества перестановок размера n с учетом возможного присутствия неподвижных точек количества k в любом их расположении.
Для функционирования программы необходима операционная система Windows 7 или выше.
Программа разработана на языке С++ с использованием стандартных библиотек C++ в среде разработки Microsoft Visual Studio.
Программа должна получать два аргумента командной строки: имя входного файла и имя выходного файла в формате 'txt'

Пример команды запуска программы:
* \code
./findRearrangementsWithFixedPoints.exe ./input.txt ./output.txt
* \endcode

* \author Anastasia Igrunova
* \date June 2025
* \version 1.0
*/

#include <iostream>
#include <locale>
#include "functions.h"

/*!
 * \brief Главная функция программы
 * \param [in] argc - количество переданных аргументов командной строки
 * \param [in] argv - аргументы командной строки
 * \param [in] argv[0] - аргумент запуска программы
 * \param [in] argv[1] - путь к входному файлу
 * \param [in] argv[2] - путь к выходному файлу
 * \return 0 - программа завершилась без исключений
 */
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");

    vector<string> file_content;

    //если передается не 3 параметра как положено
    if (argc != 3)
    {
        cerr << "Неправильно указаны параметры запуска. "
            "Убедитесь, что параметры соответствуют шаблону: \n"
            << argv[0] << "<path/to/input_file> <path/to/save_file>\n";
        return 1;
    }

    //объявление входных и выходных файлов
    ifstream input_file(argv[1]);
    ofstream output_file(argv[2]);

    if (!input_file.is_open())
    {
        cerr << "Неверно указан файл с входными данными.\n Возможно, файл не существует или нет прав на открытие." << argv[1] << '\n';
        return 1;
    }

    //если не удалось считать данные из файла
    if (!readFile(input_file, file_content))
    {
        //вывести ошибку о невозможности записи из файла
        cerr << "Не удалось записать данные из входного файла "
            "Возможно, файл пустой. " << '\n';
        return 1;
    }

    //проверка что во входном файле только 1 строка
    if (file_content.size() != 1)
    {
        cerr << "Неверное количество строк в файле.\n В файле должна быть только одна строка с параметрами.";
        return 1;
    }

    vector<string> splited_string;

    DataErrors check_input = validateInputData(file_content[0], splited_string);

    if (check_input == TOO_MANY_SYMBOLS)
    {
        cerr << "Некорректное количество элементов в строке. \nОжидаемое количество: 7 \nПолученное количество: " << splited_string.size() << endl;

        return 1;
    }
    else if (check_input == WRONG_INPUT)
    {
        cerr << "Строка с данными не соответствует шаблону \"n = <число>, k = <число>\". Введите корректную строку. " << endl;

        return 1;
    }
    else if (check_input == NO_INT)
    {
        cerr << "Значения переменных не целые числа. \nВведите значения переменных в формате целого числа" << endl;

        return 1;
    }

    //конвертация строковых значений в целочисленное для дальнейшей работы
    int permutation_size = stoi(splited_string[2]);
    int max_fixed_points = stoi(splited_string[6]);

    //проверка на корректный диапазон значений
    if (max_fixed_points > permutation_size || (permutation_size == 1 && max_fixed_points != 0))
    {
        cerr << "Значения вне допустимого диапазона.\nУбедитесь, что значения входят в диапазон:\n1<=n<=9\n0<=k<=n\n" << endl;
        return 1;
    }

    //объявление необходимых данных
    vector<int>current_permutation(permutation_size);
    int index = 0;
    vector<bool> used_elements(permutation_size, false);
    int fixed_points_count = 0;
    vector<vector<int>> generated_permutations;

    //вызов главной рекурсивной вычислительной функции
    generateRearrangements(current_permutation, index, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

    //запись в выходной файл
    recOutputFile(generated_permutations, output_file);

    return 0;
}