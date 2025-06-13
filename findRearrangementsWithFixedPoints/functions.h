/*!
* \file
* \brief ������ ���� �������� ��������� ������� ��� ������ ��������� findRearrangementsWithFixedPoints.
*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/*!
* \brief ������������ ����� ������, ������� ����� ���������� � �������� �������
*/
enum DataErrors
{
    NO_DATA_ERROR, //!< ������ � ������� ���

    TOO_MANY_SYMBOLS, //!< ������� ����� �������, ��� �� ������������� �������

    WRONG_INPUT, //!< �������������� ������� ������� �������

    NO_INT //!< � ������ ������� �� ������������� ��������
};

/*!
* \brief ������� ��� ���������� ������ �� �������� �����
* \param [in] - input_file_path - ���������� ��� ������������� ���� � �������� �����
* \param [in] - params - ���������, ��������� �� �������� �����
* \return true - ������ ������� �������
* \return false - ������ �� ������� �������
*/
bool readFile(ifstream& input_file, vector<string>& file_content);

/*!
* \brief �������, ������� ��������� ������ �� ��������� �� �������� ��� ������ ������������
* \param [in] input_data - ������, ������� ���������� ������� �� �������
* \return ��������� � ���������, �� ������� ���� ������� ������
*/
vector<string> splitString(string& input_string);

/*!
* \brief �������, �������������� ������ � �������� �������
* \param [in] input_string - ������, ������� �� ��������� �� ������������
* \param [in] string_elements - ������� � ����� ������ ��� �������� �� ������������
* \return true - ������ ������� ���������
* \return false - ������ ������� �����������
*/
DataErrors validateInputData(string& input_string, vector<string>& string_elements);

/*!
* \brief �������, ��������� ������������ ������������ � ������������ ������� ��������� ������� � ���������� ��������������
* \param [in] current_permutation - ������� ������������ ������� �� ��������
* \param [in] index - ������� �������� ������� �� ������������� �� ������� ������
* \param [in] used_elements - ��������� � ��� ��������������� �������
* \param [in] max_fixed_points - �������� ����������� ����� ������� ����� ���� � ������������
* \param [in] fixed_points_count - ������� ����������� ����� � ������������
* \param [in] generated_permutations - ��������� � ��� ���������������� ��������������, ������� �� ��������� ����� ��������� � ������ ������� ��������
*/
void generateRearrangements(vector<int>& current_permutation, int index, vector<bool>& used_elements, int max_fixed_points, int fixed_points_count, vector<vector<int>>& generated_permutations);

/*!
* \brief ������� ��� ������ ������ � �������� ����
* \param [in] generated_permutations - ��� ��������������� ������������, ������� ����� �������� � �������� ����
* \param [in] output_file - �������� ����, � ������� ������������ ������
*/
void recOutputFile(vector<vector<int>>& generated_permutations, ofstream& output_file);