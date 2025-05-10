#include <iostream>
#include <vector>

using namespace std;

//������ � ���������� ������
enum DataErrors
{
    //������ ���
    NO_DATA_ERROR,
    //������� ����� �������, ��� �� ������������� �������
    TOO_MANY_SYMBOLS,
    //�������������� ������� ������� �������
    WRONG_INPUT,
    //� ������ ������� �� ������������� ��������
    NO_INT
};

/*������� ��� ��������� � �������� �������� �����
* \param[in] - input_file_path - ���������� ��� ������������� ���� � �������� �����
* \param[in] - file_content - ���������� �������� �����
* \return true - ������� ���� ������� ������� � ������� �� ���� ������
* \return false - ������� ���� �� ������� ������� �/��� ������� �� ���� ������
*/
bool readFile(ifstream& input_file, vector<string>& file_content);

/*������� ��� ���������� ������ �� �����, ������� � �����������
* \param[in] input_string - ������, ������� ���������� ���������
* \return ��������� �� ������� � ���������, �� ������� ���� ������� ������
*/
vector<string> tokenizeString(string& input_string);

/* ������� ��� ��������� ������ �� ���������� ����
* \param[in] input_string - ������, ������� �� ��������� �� ������������
* \param[in] tokens - ������� � ����� ������ ��� �������� �� ������������
* \return true - ������ ������� ���������
* \return false - ������ ������� ����������� 
*/
DataErrors validateInputData(string input_string, vector<string> tokens);

/*����������� ������� �������������� �������
* \param[in] current_permutation - ������� ������������ ������� �� ��������
* \param[in] index - ������� �������� ������� �� ������������� �� ������� ������
* \param[in] used_elements - ��������� � ��� ��������������� �������
* \param[in] max_fixed_points - �������� ����������� ����� ������� ����� ���� � ������������
* \param[in] fixed_points_count - ������� ����������� ����� � ������������
* \param[in] generated_permutations - ��������� � ��� ���������������� ��������������, ������� �� ��������� ����� ��������� � ������ ������� ��������
*/
void generate_rearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations);