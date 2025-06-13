/*!
* \file
* \brief ������ ���� �������� ������� ������� ��������� findRearrangementsWithFixedPoints.
*
* \mainpage ������������ ��� ��������� "Find Rearrangements With Fixed Points (findRearrangementsWithFixedPoints)"
��������� ������������� ��� ���������� ���������� ������������ ������� n � ������ ���������� ����������� ����������� ����� ���������� k � ����� �� ������������.
��� ���������������� ��������� ���������� ������������ ������� Windows 7 ��� ����.
��������� ����������� �� ����� �++ � �������������� ����������� ��������� C++ � ����� ���������� Microsoft Visual Studio.
��������� ������ �������� ��� ��������� ��������� ������: ��� �������� ����� � ��� ��������� ����� � ������� 'txt'

������ ������� ������� ���������:
* \code
./findRearrangementsWithFixedPoints.exe ./input.txt ./output.txt
* \endcode

* \author Anastasia Igrunova
* \date June 2025
* \version 1.0
*/

#include <iostream>
#include <locale>
#include "functions.h"

/*!
 * \brief ������� ������� ���������
 * \param [in] argc - ���������� ���������� ���������� ��������� ������
 * \param [in] argv - ��������� ��������� ������
 * \param [in] argv[0] - �������� ������� ���������
 * \param [in] argv[1] - ���� � �������� �����
 * \param [in] argv[2] - ���� � ��������� �����
 * \return 0 - ��������� ����������� ��� ����������
 */
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");

    vector<string> file_content;

    //���� ���������� �� 3 ��������� ��� ��������
    if (argc != 3)
    {
        cerr << "����������� ������� ��������� �������. "
            "���������, ��� ��������� ������������� �������: \n"
            << argv[0] << "<path/to/input_file> <path/to/save_file>\n";
        return 1;
    }

    //���������� ������� � �������� ������
    ifstream input_file(argv[1]);
    ofstream output_file(argv[2]);

    if (!input_file.is_open())
    {
        cerr << "������� ������ ���� � �������� �������.\n ��������, ���� �� ���������� ��� ��� ���� �� ��������." << argv[1] << '\n';
        return 1;
    }

    //���� �� ������� ������� ������ �� �����
    if (!readFile(input_file, file_content))
    {
        //������� ������ � ������������� ������ �� �����
        cerr << "�� ������� �������� ������ �� �������� ����� "
            "��������, ���� ������. " << '\n';
        return 1;
    }

    //�������� ��� �� ������� ����� ������ 1 ������
    if (file_content.size() != 1)
    {
        cerr << "�������� ���������� ����� � �����.\n � ����� ������ ���� ������ ���� ������ � �����������.";
        return 1;
    }

    vector<string> splited_string;

    DataErrors check_input = validateInputData(file_content[0], splited_string);

    if (check_input == TOO_MANY_SYMBOLS)
    {
        cerr << "������������ ���������� ��������� � ������. \n��������� ����������: 7 \n���������� ����������: " << splited_string.size() << endl;

        return 1;
    }
    else if (check_input == WRONG_INPUT)
    {
        cerr << "������ � ������� �� ������������� ������� \"n = <�����>, k = <�����>\". ������� ���������� ������. " << endl;

        return 1;
    }
    else if (check_input == NO_INT)
    {
        cerr << "�������� ���������� �� ����� �����. \n������� �������� ���������� � ������� ������ �����" << endl;

        return 1;
    }

    //����������� ��������� �������� � ������������� ��� ���������� ������
    int permutation_size = stoi(splited_string[2]);
    int max_fixed_points = stoi(splited_string[6]);

    //�������� �� ���������� �������� ��������
    if (max_fixed_points > permutation_size || (permutation_size == 1 && max_fixed_points != 0))
    {
        cerr << "�������� ��� ����������� ���������.\n���������, ��� �������� ������ � ��������:\n1<=n<=9\n0<=k<=n\n" << endl;
        return 1;
    }

    //���������� ����������� ������
    vector<int>current_permutation(permutation_size);
    int index = 0;
    vector<bool> used_elements(permutation_size, false);
    int fixed_points_count = 0;
    vector<vector<int>> generated_permutations;

    //����� ������� ����������� �������������� �������
    generateRearrangements(current_permutation, index, used_elements, max_fixed_points, fixed_points_count, generated_permutations);

    //������ � �������� ����
    recOutputFile(generated_permutations, output_file);

    return 0;
}