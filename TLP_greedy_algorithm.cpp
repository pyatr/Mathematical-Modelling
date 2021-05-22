#include "pch.h"
#include <iostream>
#include <locale.h>
#include <vector>
#include <time.h>
#include <string>

#pragma warning(disable:4996)

using namespace std;

const int MATRIX_SIZE = 9;

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
	bool checked[MATRIX_SIZE];
	string lines[MATRIX_SIZE - 1]; 
	//string names[MATRIX_SIZE] = { "a", "b", "c", "d", "e" };
	
	string names[MATRIX_SIZE] = { "Москва", "Санкт - Петербург", "Волгоград", "Тула", "Новороссийск", "Смоленск", "Мурманск", "Севастополь", "Керчь" };
	
	/*lines[0] = "74, 142, 218, 275, 346, 302, 224, 186";
	lines[1] = "69, 152, 201, 271, 263, 185, 193";
	lines[2] = "66, 125, 195, 192, 127, 136";
	lines[3] = "59, 129, 128, 148, 184";
	lines[4] = "84, 117, 195, 230";
	lines[5] = "105, 186, 220";
	lines[6] = "79, 114";
	lines[7] = "38";*/
	lines[0] = "634, 932, 173, 1226, 369, 1487, 1278, 1159";
	lines[1] = "1545, 775, 1763, 582, 1012, 1724, 1672";
	lines[2] = "774, 678, 1090, 2338, 956, 714";
	lines[3] = "1053, 365, 1660, 1111, 986";
	lines[4] = "1191, 2710, 336, 124";
	lines[5] = "1578, 1142, 1094";
	lines[6] = "2715, 2633";
	lines[7] = "247";
	/*lines[0] = "707, 1075, 1606, 411, 1795, 3395, 9165";
	lines[1] = "1783, 2268, 1249, 2402, 3936, 9909";
	lines[2] = "520, 1266, 2260, 3712, 9488";
	lines[3] = "1634, 2437, 3890, 9666";
	lines[4] = "1425, 2917, 8692";
	lines[5] = "1599, 7379";
	lines[6] = "5782";*/

	/*lines[0] = "400 2400 3500 1800";
	lines[1] = "1400 2500 3500";
	lines[2] = "2200 1900";
	lines[3] = "2600";*/
	/*lines[0] = "789 1622 1811 2814";
	lines[1] = "1098 1117 1162";
	lines[2] = "186 1473";
	lines[3] = "1294";*/
	int C[MATRIX_SIZE][MATRIX_SIZE];
	for (i = 0; i < MATRIX_SIZE; i++)
	{
		checked[i] = false;
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
		}
	}
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
	int start_point = 0;
	int current_point = start_point;
	bool allPointsVisited = false;
	int minDistance = -1;
	int minDistancePoint = current_point;
	int distance = 0;
	int visited = 0;
	cout << endl;
	int attempt = 0, attmepts = MATRIX_SIZE + 1;
	do
	{
		checked[current_point] = true;
		visited++;
		minDistance = -1;
		minDistancePoint = current_point;
		for (i = 0; i < MATRIX_SIZE; i++)
		{
			if (visited < MATRIX_SIZE)
			{
				if (current_point != i && !checked[i])
				{
					if (minDistance == -1 || minDistance > C[i][current_point])
					{
						minDistance = C[i][current_point];
						minDistancePoint = i;
					}
				}
			}
			else
			{
				cout << "Все точки посещены, возвращаемся в " << names[start_point] << endl;
				minDistance = C[i][current_point];
				minDistancePoint = start_point;
				i = MATRIX_SIZE;
			}
		}
		distance += minDistance;
		cout << "Расстояние от " << names[current_point] << " до " << names[minDistancePoint] << " равно " << minDistance << ", общая дистанция равна " << distance << endl;
		current_point = minDistancePoint;

		allPointsVisited = true;
		for (i = 0; i < MATRIX_SIZE; i++)
		{
			if (checked[i] == false)
			{
				allPointsVisited = false;
			}
		}
		cout << endl;
		attempt++;
	} while (!allPointsVisited && attempt < attmepts);

	return 0;
}