#include <iostream>
#include <vector>
#include "functions.h"

using namespace std;

bool readFile(const string& input_file_path, vector<string>& file_content)
{
    //здесь будет псевдокод
    return false;
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

int main()
{
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

