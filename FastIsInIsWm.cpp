#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#include <string>
#include <locale>

#include <vector>
#include <algorithm>
#include <cctype>


bool iswm(std::string const &_sMask, std::string const &_Text)
{
	std::string sMask;

	{
		char cLast = 0;
		size_t iLast = 0;

		for (size_t i = 0; i < _sMask.size(); i++)
		{
			char c = _sMask[i];
			if (!(cLast == c && c == '*' || !isgraph(c)))
			{
				sMask.push_back(_sMask[i]);
				iLast++;
			}

			cLast = c;
		}
	}

	// ������� ���������� ��������� �� ������-�� ���������
	// ���� - ������ �� ����, ���������
	// ����� - ���������
	auto _GetStates = [&sMask](size_t _State, char _cInput)
	{
		std::vector<size_t> States;

		// ���� ������� ������� - ?, �� ���������� � ��� ������
		// ��� ���� ������� ������� == �������� ������� - ��������� ������
		if (sMask[_State + 1] == '?' || sMask[_State + 1] == _cInput)
		{
			States.push_back(_State + 1);
		}

		// ���� ������� ������� *, �� ������� ��� � ��
		if (_State != -1 && sMask[_State] == '*')
		{
			States.push_back(_State);
		}

		if (sMask[_State + 1] == '*')
		{
			States.push_back(_State + 1);

			// * = 0
			if (_State + 2 < sMask.size() && (sMask[_State + 2] == '?' || sMask[_State + 2] == _cInput))
			{
				States.push_back(_State + 2);
			}
		}

		return States;
	};

	// ������ ���������, �������� ������� ���������(�.�. �������)
	std::vector<size_t> States(1, -1);

	// ��� ����� �� ������
	for (char cSource : _Text)
	{
		// ������� ����� �� ��������������
		if (States.empty())
			break;

		std::vector<size_t> NewStates;

		// �� �� ����� �� ���, ������ �� ����� ������������ ���!
		for (size_t iPos : States)
		{
			auto states = _GetStates(iPos, cSource);
			NewStates.insert(NewStates.end(), states.begin(), states.end());
		}

		States.assign(NewStates.begin(), NewStates.end());
	}


	// ����������� - ��������� ) ��������
	for (size_t i : States)
	{
		if (i == sMask.size() - 1)
		{
			return true;
		}
	}

	return false;
}

int main()
{
	std::string sMask = "a?*b*c";
	std::string sText = "apbdsadasc";

	printf("\"%s\" by mask \"%s\": %d\n", sText.c_str(), sMask.c_str(), iswm(sMask, sText));

	_getch();
	return 0;
};