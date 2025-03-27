#include <iostream>
#include <vector>

using namespace std;

/*рекурсивная главная вычислительная функция
* \param[in] current_permutation - текущая перестановка которую мы собираем
* \param[in] index - позиция элемента которую мы рассматриваем на текущий момент
* \param[in] used_elements - контейнер с уже использованными числами
* \param[in] max_fixed_points - максимум неподвижных точек которые могут быть в перестановке
* \param[in] fixed_points_count - счетчик неподвижных точек в перестановке
* \param[in] generated_permutations - контейнер с уже сгенерированными перестановками, который мы постоянно будем пополнять с каждым вызовом рекурсии
*/
void recursion_for_rearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations);