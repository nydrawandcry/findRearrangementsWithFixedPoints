#include <iostream>
#include <vector>

using namespace std;

//ошибки с обработкой данных
enum DataErrors
{
    //ошибок нет
    NO_DATA_ERROR,
    //слишком много токенов, что не соответствует шаблону
    TOO_MANY_SYMBOLS,
    //несоответствие токенов нужному шаблону
    WRONG_INPUT,
    //в нужных токенах не целочисленные значения
    NO_INT
};

/*функция для обработки и открытия входного файла
* \param[in] - input_file_path - абсолютный или относительный путь к входному файлу
* \param[in] - file_content - содержимое входного файла
* \return true - входной файл удалось открыть и считать из него данные
* \return false - входной файл не удалось открыть и/или считать из него данные
*/
bool readFile(ifstream& input_file, vector<string>& file_content);

/*функция для разделения строки на слова, символы и разделители
* \param[in] input_string - строка, которую необходимо разделить
* \return контейнер со словами и символами, на которые была разбита строка
*/
vector<string> tokenizeString(string& input_string);

/* функция для обработки строки на корректный ввод
* \param[in] input_string - строка, которую мы проверяем на корректность
* \param[in] tokens - символы и слова строки для проверки на корректность
* \return true - данные введены корректно
* \return false - данные введены некорректно 
*/
DataErrors validateInputData(string input_string, vector<string> tokens);

/*рекурсивная главная вычислительная функция
* \param[in] current_permutation - текущая перестановка которую мы собираем
* \param[in] index - позиция элемента которую мы рассматриваем на текущий момент
* \param[in] used_elements - контейнер с уже использованными числами
* \param[in] max_fixed_points - максимум неподвижных точек которые могут быть в перестановке
* \param[in] fixed_points_count - счетчик неподвижных точек в перестановке
* \param[in] generated_permutations - контейнер с уже сгенерированными перестановками, который мы постоянно будем пополнять с каждым вызовом рекурсии
*/
void generate_rearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations);