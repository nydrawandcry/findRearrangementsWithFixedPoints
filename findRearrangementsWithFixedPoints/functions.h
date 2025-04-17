#include <iostream>
#include <vector>

using namespace std;


/*������� ��� ��������� � �������� �������� �����
* \param[in] - input_file_path - ���������� ��� ������������� ���� � �������� �����
* \param[in] - file_content - ���������� �������� �����
* \return true - ������� ���� ������� ������� � ������� �� ���� ������
* \return false - ������� ���� �� ������� ������� �/��� ������� �� ���� ������
*/
bool readFile(const string& input_file_path, vector<string>& file_content);

/*����������� ������� �������������� �������
* \param[in] current_permutation - ������� ������������ ������� �� ��������
* \param[in] index - ������� �������� ������� �� ������������� �� ������� ������
* \param[in] used_elements - ��������� � ��� ��������������� �������
* \param[in] max_fixed_points - �������� ����������� ����� ������� ����� ���� � ������������
* \param[in] fixed_points_count - ������� ����������� ����� � ������������
* \param[in] generated_permutations - ��������� � ��� ���������������� ��������������, ������� �� ��������� ����� ��������� � ������ ������� ��������
*/
void generate_rearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations);