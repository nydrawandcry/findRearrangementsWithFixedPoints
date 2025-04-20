#include <iostream>
#include <vector>
#include <fstream>
#include <locale>
#include "functions.h"

using namespace std;

bool readFile(ifstream& input_file, vector<string>& file_content)
{
    //1.1.Если входной невозможно открыть
    {
        //1.1.1.Проверить, доступен ли к открытию выходной файл.Если доступен
        {
            //1.1.1.1.Занести ошибку об отсутствии доступа к файлу «имя файла» в файл
        }
        //1.1.2.Иначе
        {
            //1.1.2.1.Вывести ошибку о невозможности открыть выходной и входной файл в стандартный поток ошибок
        }
    }
    //1.2.Иначе
    {
        //1.2.1.Для каждой строки файла
        //1.2.1.1.Считать строку из файла в переменные
        //1.2.2.Закрыть файл
    }
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
        cerr << "Неверно указан файл с входными данными. Возможно, файл не существует." << argv[1] << '\n';
        return 1;
    }

    //если входной файл удалось не удалось прочитать и записать данные
    {
        //вывести ошибку о невозможности записи из файла
    }
    
    //обработать данные, полученные из входного файла

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

