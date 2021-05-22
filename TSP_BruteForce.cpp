#include "pch.h"
#include <iostream>
#include <locale.h>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>

#pragma warning(disable:4996)

using namespace std;

const int MATRIX_SIZE = 6;

int factorial(int n, int degree)
{
	if (degree > 0)
	{
		n *= MATRIX_SIZE - degree;
		degree--;
		factorial(n, degree);
	}
	else
	{
		return n;
	}	
}

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
	/*lines[0] = "13 25 13";
	lines[1] = "23 13";
	lines[2] = "32";*/
	/*lines[0] = "686 534 595 388";
	lines[1] = "575 939 995";
	lines[2] = "423 815";
	lines[3] = "700";*/
	/*lines[0] = "789 1622 1811 2814";
	lines[1] = "1098 1117 1162";
	lines[2] = "186 1473";
	lines[3] = "1294";*/
	/*lines[0] = "1350 2410 570";
	lines[1] = "3620 3230";
	lines[2] = "1910";*/
	lines[0] = "319 168 191 207 456";
	lines[1] = "244 294 429 342";
	lines[2] = "91 277 676";
	lines[3] = "307 275";
	lines[4] = "222";
	/*lines[0] = "269 203 529";
	lines[1] = "263 793";
	lines[2] = "579";*/
	/*lines[0] = "400 2400 3500 1800";
	lines[1] = "1400 2500 3500";
	lines[2] = "2200 1900";
	lines[3] = "2600";*/
	/*
	lines[0] = "707, 1075, 1606, 411, 1795, 3395, 9165";
	lines[1] = "1783, 2268, 1249, 2402, 3936, 9909";
	lines[2] = "520, 1266, 2260, 3712, 9488";
	lines[3] = "1634, 2437, 3890, 9666";
	lines[4] = "1425, 2917, 8692";
	lines[5] = "1599, 7379";
	lines[6] = "5782";*/
	int C[MATRIX_SIZE][MATRIX_SIZE];

	for (i = 0; i < MATRIX_SIZE; i++)
	{
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
	int variant_amount = factorial(1, MATRIX_SIZE - 1);
	cout << "Количество возможных вариантов путей: " << variant_amount << endl;
	int **variants = new int*[variant_amount];
	int *sums = new int[variant_amount];

	string s = "";
	for (i = 0; i < MATRIX_SIZE - 1; i++)
		s += to_string(i + 2);

	sort(s.begin(), s.end());

	int d = 0;
	do {
		//cout << "1" << s << "1" << endl;
		cout << d + 1 << ":	";
		variants[d] = new int[MATRIX_SIZE + 1];
		variants[d][0] = 1;
		variants[d][MATRIX_SIZE] = 1;
		for (i = 1; i < MATRIX_SIZE; i++)
		{
			variants[d][i] = (int)s[i - 1] - 48;
		}
		int sum = 0;

		int prev = 0;
		int a, b, c;
		for (i = 1; i <= MATRIX_SIZE; i++)
		{
			a = prev;
			b = variants[d][i] - 1;
			prev = b;
			c = C[a][b];
			sum += c;
			cout << c;
			//cout << "[" << a + 1 << "/" << b + 1 << "]";
			if (i < MATRIX_SIZE)
				cout << " + ";
			else
				cout << " = ";
		}
		sums[d] = sum;
		cout << sums[d] << endl;
		d++;
	} while (next_permutation(s.begin(), s.end()));

	int min = -1;
	int minnum = -1;
	int minnum_reverse = 0;
	for (i = 0; i < variant_amount; i++)
	{
		if (min == -1 || min > sums[i])
		{
			min = sums[i];
			minnum = i + 1;
		}
	}

	for (i = variant_amount - 1; i >= 0; i--)
	{
		if (sums[i] == min)
		{
			minnum_reverse = i + 1;
			i = -1;
		}
	}

	cout << "Самый короткий вариант №" << minnum << " и его обратный цикл №" << minnum_reverse << " имеют длину " << min << endl;

	delete(sums);
	for (i = 0; i < variant_amount; i++)
	{
		delete(variants[i]);
	}
	delete(variants);
	return 0;
}