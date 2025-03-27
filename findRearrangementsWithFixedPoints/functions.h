#include <iostream>
#include <vector>

using namespace std;

/*����������� ������� �������������� �������
* \param[in] current_permutation - ������� ������������ ������� �� ��������
* \param[in] index - ������� �������� ������� �� ������������� �� ������� ������
* \param[in] used_elements - ��������� � ��� ��������������� �������
* \param[in] max_fixed_points - �������� ����������� ����� ������� ����� ���� � ������������
* \param[in] fixed_points_count - ������� ����������� ����� � ������������
* \param[in] generated_permutations - ��������� � ��� ���������������� ��������������, ������� �� ��������� ����� ��������� � ������ ������� ��������
*/
void recursion_for_rearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations);