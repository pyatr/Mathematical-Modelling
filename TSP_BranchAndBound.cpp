#include "pch.h"
#include <iostream>
#include <locale.h>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>

#pragma warning(disable:4996)

using namespace std;

const int MATRIX_SIZE = 7;

vector<string> Split(string &s)
{
	std::vector<string> items;
	char *str = new char[s.length() + 1];
	strcpy(str, s.c_str());
	char delim[] = " ";
	char *ptr = strtok(str, delim);
	while (ptr != NULL)
	{
		string str2(ptr);
		items.push_back(str2);
		ptr = strtok(NULL, delim);
	}
	delete(str);
	delete(ptr);
	return items;
}

void swap(int &a, int &b)
{
	int c = b;
	b = a;
	a = c;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	int i, j;
	string lines[MATRIX_SIZE - 1];
	/*lines[0] = "299 564 459 369";
	lines[1] = "285 180 395";
	lines[2] = "225 660";
	lines[3] = "555";*/
	/*lines[0] = "686 534 595 388";
	lines[1] = "575 939 995";
	lines[2] = "423 815";
	lines[3] = "700";*/
	/*lines[0] = "789 1622 1811 2814";
	lines[1] = "1098 1117 1162";
	lines[2] = "186 1473";
	lines[3] = "1294";*/
	/*lines[0] = "74, 142, 218, 275, 346, 302, 224, 186";
	lines[1] = "69, 152, 201, 271, 263, 185, 193";
	lines[2] = "66, 125, 195, 192, 127, 136";
	lines[3] = "59, 129, 128, 148, 184";
	lines[4] = "84, 117, 195, 230";
	lines[5] = "105, 186, 220";
	lines[6] = "79, 114";
	lines[7] = "38";*/
	/*lines[0] = "707, 1075, 1606, 411, 1795, 3395, 9165";
	lines[1] = "1783, 2268, 1249, 2402, 3936, 9909";
	lines[2] = "520, 1266, 2260, 3712, 9488";
	lines[3] = "1634, 2437, 3890, 9666";
	lines[4] = "1425, 2917, 8692";
	lines[5] = "1599, 7379";
	lines[6] = "5782";*/
	lines[0] = "290, 115, 82, 200, 49, 175";
	lines[1] = "270, 283, 100, 241, 210";
	lines[2] = "156, 180, 92, 130";
	lines[3] = "166, 103, 177";
	lines[4] = "151, 130";
	lines[5] = "126";

	int C[MATRIX_SIZE][MATRIX_SIZE];
	int tovisit[MATRIX_SIZE];
	int original[MATRIX_SIZE][MATRIX_SIZE];
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		tovisit[i] = 0;
		vector<string> numbers;
		if (i < MATRIX_SIZE - 1)
			numbers = Split(lines[i]);
		int a = 0;
		for (j = 0; j < MATRIX_SIZE; j++)
		{
			if (j > i && i < MATRIX_SIZE - 1)
			{
				C[i][j] = stoi(numbers[a]);
				C[j][i] = C[i][j];
				a++;
			}
			if (i == j)
				C[i][j] = -1;
			original[i][j] = C[i][j];
		}
	}

	cout << "Начало" << endl;
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		for (j = 0; j < MATRIX_SIZE; j++)
		{
			if (C[i][j] == -1)
				cout << "M ";
			else
				cout << C[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	int di[MATRIX_SIZE], dj[MATRIX_SIZE];
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		int min = -1;
		for (j = 0; j < MATRIX_SIZE; j++)
		{
			if (C[i][j] != -1)
			{
				if (min == -1 || min > C[i][j])
				{
					min = C[i][j];
				}
			}
		}
		di[i] = min;
	}

	cout << "Константы приведения в строках" << endl;
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		for (j = 0; j < MATRIX_SIZE; j++)
		{
			if (C[i][j] == -1)
				cout << "M ";
			else
				cout << C[i][j] << " ";
		}
		cout << "	|" << di[i] << endl;
	}
	cout << endl;

	for (i = 0; i < MATRIX_SIZE; i++)
		for (j = 0; j < MATRIX_SIZE; j++)
			if (C[i][j] != -1)
				C[i][j] -= di[i];

	cout << "Редукция матрицы" << endl;
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		for (j = 0; j < MATRIX_SIZE; j++)
		{
			if (C[i][j] == -1)
				cout << "M ";
			else
				cout << C[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (i = 0; i < MATRIX_SIZE; i++)
	{
		int min = -1;
		for (j = 0; j < MATRIX_SIZE; j++)
			if (C[j][i] != -1)
				if (min == -1 || min > C[j][i])
					min = C[j][i];
		dj[i] = min;
	}

	cout << "Константы приведения в столбцах" << endl;
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		for (j = 0; j < MATRIX_SIZE; j++)
		{
			if (C[i][j] == -1)
				cout << "M ";
			else
				cout << C[i][j] << " ";
		}
		cout << endl;
	}
	for (i = 0; i < MATRIX_SIZE; i++)
		cout << dj[i] << " ";
	cout << endl << endl;

	for (i = 0; i < MATRIX_SIZE; i++)
		for (j = 0; j < MATRIX_SIZE; j++)
			if (C[i][j] != -1)
				C[i][j] -= dj[j];

	cout << "Редукция матрицы" << endl;
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		for (j = 0; j < MATRIX_SIZE; j++)
		{
			if (C[i][j] == -1)
				cout << "M ";
			else
				cout << C[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Переходим к основному этапу" << endl;

	bool eachRowAndColumnHasZeroes = false;
	bool used_r[MATRIX_SIZE], used_c[MATRIX_SIZE];
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		used_r[i] = false;
		used_c[i] = false;
	}

	int remaining = MATRIX_SIZE;

	int mri, mrj;
	int maxrating = -1;
	do
	{
		cout << endl << "Выполняем итерацию" << endl;
		bool rowHasZero[MATRIX_SIZE], columnHasZero[MATRIX_SIZE];
		for (i = 0; i < MATRIX_SIZE; i++)
		{
			di[i] = 0;
			dj[i] = 0;
			rowHasZero[i] = false;
			columnHasZero[i] = false;
			if (!used_r[i])
			{
				for (j = 0; j < MATRIX_SIZE; j++)
				{
					if (!used_c[j])
					{
						if (C[i][j] == -1)
							cout << "M ";
						else
							cout << C[i][j] << " ";
					}
				}
				cout << endl;
			}
		}
		cout << endl;

		for (i = 0; i < MATRIX_SIZE; i++)
		{
			if (!used_r[i])
			{
				for (j = 0; j < MATRIX_SIZE; j++)
				{
					if (!used_c[j])
					{
						if (C[i][j] == 0)
							rowHasZero[i] = true;
						if (C[j][i] == 0)
							columnHasZero[j] = true;
					}
				}
			}
		}

		eachRowAndColumnHasZeroes = true;
		for (i = 0; i < MATRIX_SIZE; i++)
		{
			if (!rowHasZero[i])
			{
				if (!used_r[i])
				{
					eachRowAndColumnHasZeroes = false;
					cout << "В строке " << i << " нет нулей" << endl;
				}
			}
			if (!columnHasZero[i])
			{
				if (!used_c[i])
				{
					eachRowAndColumnHasZeroes = false;
					cout << "В столбце " << i << " нет нулей" << endl;
				}
			}
		}

		if ((!eachRowAndColumnHasZeroes || remaining == MATRIX_SIZE) && remaining > 1)
		{
			for (i = 0; i < MATRIX_SIZE; i++)
			{
				int min = -1;
				for (j = 0; j < MATRIX_SIZE; j++)
				{
					if (C[i][j] != -1)
					{
						if (min == -1 || min > C[i][j])
						{
							min = C[i][j];
						}
					}
				}
				di[i] = min;
			}

			cout << "В одной из строк или столбцов нет нулей; Проведем редукцию матрицы" << endl << "Константы приведения в строках" << endl;
			for (i = 0; i < MATRIX_SIZE; i++)
			{
				if (!used_r[i])
				{
					for (j = 0; j < MATRIX_SIZE; j++)
					{
						if (!used_c[j])
						{
							if (C[i][j] == -1)
								cout << "M ";
							else
								cout << C[i][j] << " ";
						}
					}
					cout << "	|" << di[i] << endl;
				}
			}
			cout << endl;

			cout << "Редукция матрицы по строкам" << endl;
			for (i = 0; i < MATRIX_SIZE; i++)
			{
				if (!used_r[i])
				{
					for (j = 0; j < MATRIX_SIZE; j++)
					{
						if (!used_c[j])
						{
							if (C[i][j] == -1)
								cout << "M ";
							else
							{
								C[i][j] -= di[i];
								cout << C[i][j] << " ";
							}
						}
					}
					cout << endl;
				}
			}
			cout << endl;

			for (i = 0; i < MATRIX_SIZE; i++)
			{
				columnHasZero[i] = false;
				if (!used_r[i])
				{
					for (j = 0; j < MATRIX_SIZE; j++)
					{
						if (!used_c[j])
						{
							if (C[i][j] == 0)
								columnHasZero[j] = true;
						}
					}
				}
			}

			for (i = 0; i < MATRIX_SIZE; i++)
			{
				int min = -1;
				if (!used_r[i])
				{
					for (j = 0; j < MATRIX_SIZE; j++)
					{
						if (!used_c[j] && !columnHasZero[j])
						{
							if (C[j][i] != -1)
								if (min == -1 || min > C[j][i])
									min = C[j][i];
						}
					}
				}
				if (columnHasZero[j])
					min = 0;
				dj[i] = min;
			}

			cout << "Константы приведения в столбцах" << endl;
			for (i = 0; i < MATRIX_SIZE; i++)
			{
				if (!used_r[i])
				{
					for (j = 0; j < MATRIX_SIZE; j++)
					{
						if (!used_c[j])
						{
							if (C[i][j] == -1)
								cout << "M ";
							else
								cout << C[i][j] << " ";
						}
					}
					cout << endl;
				}
			}

			for (i = 0; i < MATRIX_SIZE; i++)
			{
				if (!used_c[i])
				{
					cout << dj[i] << " ";
				}
			}
			cout << endl << endl;

			cout << "Редукция матрицы по столбцам" << endl;
			for (i = 0; i < MATRIX_SIZE; i++)
			{
				if (!used_r[i])
				{
					for (j = 0; j < MATRIX_SIZE; j++)
					{
						if (!used_c[j])
						{
							if (C[i][j] == -1)
								cout << "M ";
							else
							{
								C[i][j] -= dj[j];
								cout << C[i][j] << " ";
							}
						}
					}
					cout << endl;
				}
			}
			cout << endl;
		}
		else
		{
			cout << "В каждой строке и каждом столбце есть нулевые элементы, поэтому нет необходимости проводить редукцию таблицы" << endl;
		}

		maxrating = 0;
		for (i = 0; i < MATRIX_SIZE; i++)
		{
			if (!used_r[i])
			{
				for (j = 0; j < MATRIX_SIZE; j++)
				{
					if (!used_c[j])
					{
						if (C[i][j] == 0)
						{
							int k, mini = -1, minj = -1;
							for (k = 0; k < MATRIX_SIZE; k++)
								if (k != i && C[k][j] != -1 && !used_r[k])
									if (minj == -1 || minj > C[k][j])
										minj = C[k][j];

							for (k = 0; k < MATRIX_SIZE; k++)
								if (k != j && C[i][k] != -1 && !used_c[k])
									if (mini == -1 || mini > C[i][k])
										mini = C[i][k];
							int rating = mini + minj;
							if (rating > maxrating)
							{
								maxrating = rating;
								mri = i;
								mrj = j;
							}
							cout << "Оценка " << i << "/" << j << ": [" << mini << "+" << minj << "] = " << rating << endl;
						}
					}
				}
			}
		}

		cout << "Максимальная оценка равна " << maxrating << " и находится на строке " << mri << " в столбце " << mrj << endl;
		cout << "Исключаем столбец " << mrj << " и строку " << mri << endl;
		used_r[mri] = true;
		used_c[mrj] = true;
		C[mrj][mri] = -1;

		int g = mrj;
		//cout << ">>>>Посетили город " << g << endl;
		tovisit[g] = mrj;

		remaining--;
	} while (remaining > 1);

	cout << endl << "Осталась одна незамкнутая пара" << endl;
	int lasti, lastj;
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		if (!used_r[i])
		{
			lasti = i;
			for (j = 0; j < MATRIX_SIZE; j++)
			{
				if (!used_c[j])
				{
					lastj = j;
					if (C[i][j] == -1)
						cout << "M ";
					else
						cout << C[i][j] << " ";
				}
			}
			cout << endl;
		}
	}
	tovisit[0] = lastj;
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		cout << tovisit[i] + 1 << "|";
	}
	cout << endl;

	cout << endl << "Оригинальная матрица" << endl;
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		for (j = 0; j < MATRIX_SIZE; j++)
		{
			if (original[i][j] == -1)
				cout << "M ";
			else
				cout << original[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	int sum = 0;
	cout << "Подсчитаем путь" << endl;
	int prev = 0;
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		int pos = tovisit[i] + 1;
		if (pos >= MATRIX_SIZE)
			pos -= MATRIX_SIZE;
		int c = original[prev][pos];
		cout << "[" << prev << "][" << pos << "]";
		prev = pos;

		cout << c << " ";
		sum += c;
		if (i < MATRIX_SIZE - 1)
			cout << " + ";
	}
	cout << " = " << sum;
	return 0;
}