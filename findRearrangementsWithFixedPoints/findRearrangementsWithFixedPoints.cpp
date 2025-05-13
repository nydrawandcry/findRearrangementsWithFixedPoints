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

vector<string> tokenizeString(string& input_string)
{
    //для всей строки
    {
        //если символ число или буква
        {
            //начинаем выделять отдельный элемент строки
        }
        //если символ не число или буква
        {
            //если уже начали выделять отдельный элемент строки
            {
                //добавляем отделенный элемент строки в контейнер с разделенными элементами 
                    // и очищаем текущий отделенный элемент для следующего отделения нового элемента
            }
            //если перед нами белый разделитель (табуляция или пробел)
            {
                //добавляем отделенный элемент строки в контейнер с разделенными элементами и пропускаем белые разделители
            }
        }
    }

    //если после обхода всей строки еще остался отделенный элемент строки
    {
        //добавляем последний элемент
    }

    //возвращаем контейнер со всеми разделенными элементами строки
}

DataErrors validateInputData(string input_string, vector<string> tokens)
{
    //необходимо разбить строку на смиволы, слова и корректные разделители
    tokens = tokenizeString(input_string);

    //если количество элементов строки некорректно (должно быть равно 7)
    if (tokens.size() != 7)
    {
        return TOO_MANY_SYMBOLS;
    }

    //если строка не соответствует шаблону ввода
    if (tokens[0] != "n" || tokens[1] != "=" || tokens[3] != "," || tokens[4] != "k" || tokens[5] != "=")
    {
        return WRONG_INPUT;
    }

    //если элемент, с которого считывается значения для размера перестановки, пуст
    if (tokens[2].empty())
    {
        return NO_INT;
    }

    //если элемент, с которого считывается значения для размера перестановки, не равен целочисленному значению
    for (char c : tokens[2])
    {
        if (!isdigit(c))
        {
            return NO_INT;
        }
    }

    //если элемент, с которого считывается количество неподвижных точек в перестановке, пуст
    if (tokens[6].empty())
    {
        return NO_INT;
    }

    //если элемент, с которого считывается количество неподвижных точек в перестановке, не равен целочисленному значению
    for (char c : tokens[6])
    {
        if (!isdigit(c))
        {
            return NO_INT;
        }
    }

    //если все хорошо, считаем, что строка обработана успешно и всё корректно
    return NO_DATA_ERROR;
}

void generate_rearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations)
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
        generate_rearrangements(current_permutation, index + 1, used_elements, max_fixed_points, fixed_points_count + (is_fixed ? 1 : 0), generated_permutations);

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

    //обработать данные
        //для обработки данных нужна функция на обработку строки которую мы берем чтобы считать данные
        //может быть validateInputData(input_string)?

    //вызов функции по обработке входного файла
    //вызов главной рекурсивной вычислительной функции
    // 
    // Открыть выходной файл
    // Проверить, что файл доступен для записи. Если доступен
        //Записать количество сгенерированных перестановок и сами перестановки
        //Закрыть выходной файл
    //Иначе
        //Вывести ошибку о невозможности открытия выходного файла в стандартный поток ошибок
}

