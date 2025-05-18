#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#include <string>
#include "functions.h"

using namespace std;

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

DataErrors validateInputData(string input_string, vector<string> string_elements)
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

    //если элемент, с которого считывается значения для размера перестановки, пуст
    if (string_elements[2].empty())
    {
        return NO_INT;
    }

    //если элемент, с которого считывается значения для размера перестановки, не равен целочисленному значению
    for (char c : string_elements[2])
    {
        if (!isdigit(c))
        {
            return NO_INT;
        }
    }

    //если элемент, с которого считывается количество неподвижных точек в перестановке, пуст
    if (string_elements[6].empty())
    {
        return NO_INT;
    }

    //если элемент, с которого считывается количество неподвижных точек в перестановке, не равен целочисленному значению
    for (char c : string_elements[6])
    {
        if (!isdigit(c))
        {
            return NO_INT;
        }
    }

    //если все хорошо, считаем, что строка обработана успешно и всё корректно
    return NO_DATA_ERROR;
}

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
    if(!readFile(input_file, file_content))
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
    vector<bool> used_elements;
    int fixed_points_count = 0;
    vector<vector<int>> generated_permutations;

    //вызов главной рекурсивной вычислительной функции
    generateRearrangements(current_permutation, index, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

    // 
    // Открыть выходной файл
    // Проверить, что файл доступен для записи. Если доступен
        //Записать количество сгенерированных перестановок и сами перестановки
        //Закрыть выходной файл
    //Иначе
        //Вывести ошибку о невозможности открытия выходного файла в стандартный поток ошибок
}

