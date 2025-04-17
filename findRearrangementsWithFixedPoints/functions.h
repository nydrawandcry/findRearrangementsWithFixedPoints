#include <iostream>
#include <vector>

using namespace std;


/*функция для обработки и открытия входного файла
* \param[in] - input_file_path - абсолютный или относительный путь к входному файлу
* \param[in] - file_content - содержимое входного файла
* \return true - входной файл удалось открыть и считать из него данные
* \return false - входной файл не удалось открыть и/или считать из него данные
*/
bool readFile(const string& input_file_path, vector<string>& file_content);

/*рекурсивная главная вычислительная функция
* \param[in] current_permutation - текущая перестановка которую мы собираем
* \param[in] index - позиция элемента которую мы рассматриваем на текущий момент
* \param[in] used_elements - контейнер с уже использованными числами
* \param[in] max_fixed_points - максимум неподвижных точек которые могут быть в перестановке
* \param[in] fixed_points_count - счетчик неподвижных точек в перестановке
* \param[in] generated_permutations - контейнер с уже сгенерированными перестановками, который мы постоянно будем пополнять с каждым вызовом рекурсии
*/
void generate_rearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations);