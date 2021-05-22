#include "pch.h"
#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>
#include <cstdlib>

#pragma warning(disable:4996)

using namespace std;

const int TABLEWIDTH = 8;//7
const int TABLEHEIGHT = 4;

std::vector<string> Split(string &s)
{
	std::vector<string> items;
	char *str = new char[s.length() + 1];
	strcpy(str, s.c_str());
	char delim[] = ", ";
	char *ptr = strtok(str, delim);
	while (ptr != NULL)
	{
		string str2(ptr);
		items.push_back(str2);
		ptr = strtok(NULL, delim);
	}
	//std::reverse(std::begin(items), std::end(items));		
	delete(str);
	delete(ptr);
	return items;
}

float **ConvertToTable(string *Rows, string *B, string *C)
{
	int i, j;
	float **NewTable = 0;
	NewTable = new float*[TABLEHEIGHT];

	for (i = 0; i < TABLEHEIGHT; i++)
	{
		NewTable[i] = new float[TABLEWIDTH + TABLEHEIGHT - 1];
		for (j = 0; j < TABLEWIDTH + TABLEHEIGHT - 1; j++)
		{
			NewTable[i][j] = 0;
		}
		if (i < TABLEHEIGHT - 1)
			NewTable[i][TABLEWIDTH - 1 + i] = 1;
	}

	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		vector<string> numbers = Split(Rows[i]);
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			NewTable[i][j] = stof(numbers[j]);
			//cout << NewTable[i][j] << " ";
		}
		//cout << endl;
	}

	vector<string> Bs = Split(*B);
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		NewTable[i][TABLEWIDTH + TABLEHEIGHT - 1 - 1] = stof(Bs[i]);
		//cout << NewTable[i][TABLEWIDTH + TABLEHEIGHT - 1 - 1] << " ";
	}
	//cout << endl;

	vector<string> Cs = Split(*C);
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		NewTable[TABLEHEIGHT - 1][i] = stof(Cs[i])*-1;
		//cout << NewTable[TABLEHEIGHT - 1][i] << " ";
	}
	//cout << NewTable[TABLEHEIGHT - 1][TABLEWIDTH - 1] << endl;
	return NewTable;
}

void PrintTable(float **Table)
{
	int i, j;
	for (i = 0; i < TABLEHEIGHT + 1; i++)
	{
		for (j = 0; j < TABLEWIDTH + 1 + TABLEHEIGHT - 1; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					cout << "|      ";
				}
				else
				{
					if (j < TABLEWIDTH + TABLEHEIGHT - 1)
					{
						cout << "|    T" << to_string(j);
					}
					else
					{
						cout << "|     B|" << endl;
					}
				}
			}
			else
			{
				if (j > 0)
				{
					int symbols = 6;
					string numToPrint = to_string(Table[i - 1][j - 1]);
					if (numToPrint.length() > symbols)
					{
						numToPrint = numToPrint.substr(0, symbols - 1);
					}
					string Spaces = "";
					for (int k = 0; k < 6 - numToPrint.length(); k++)
					{
						Spaces += " ";
					}
					cout << "|" << Spaces << numToPrint;
					if (j == TABLEWIDTH + TABLEHEIGHT - 1)
					{
						cout << "|" << endl;
					}
				}
				else
				{
					if (i < TABLEHEIGHT)
					{
						cout << ("|    S" + to_string(i));
					}
					else
					{
						cout << ("|      ");
					}
				}
			}
		}
	}
}

void FindResolutor(float **Table, int *ResolutionI, int *ResolutionJ)
{
	cout << ("");
	*ResolutionI = 1;
	*ResolutionJ = 1;
	int i, j;
	float min = Table[0][TABLEHEIGHT - 1];
	for (j = 0; j < TABLEWIDTH + TABLEHEIGHT - 1; j++)
	{
		if (Table[TABLEHEIGHT - 1][j] < min)
		{
			min = Table[TABLEHEIGHT - 1][j];
			*ResolutionJ = j + 1;
		}
	}
	min = Table[0][TABLEWIDTH - 1 + TABLEHEIGHT - 1] / Table[0][*ResolutionJ - 1];
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		float num1 = Table[i][TABLEWIDTH - 1 + TABLEHEIGHT - 1];
		float num2 = Table[i][*ResolutionJ - 1];
		float a;
		a = num1 / num2;
		cout << num1 << "/" << num2 << "=" << a << endl;
		if (a > 0)
		{
			if (min > a || min < 0)
			{
				min = a;
				*ResolutionI = i + 1;
			}
		}
	}
	cout << "Минимальное число равно " << min << endl;
	cout << "Разрешающий элемент равен " << Table[*ResolutionI - 1][*ResolutionJ - 1] << " и находится на позиции [" << *ResolutionI << "," << *ResolutionJ << "]" << endl;
}

float **ResolveTable(float **Table, int *ResolutionI, int *ResolutionJ)
{
	int i, j;
	float **NewTable = 0;
	NewTable = new float*[TABLEHEIGHT];
	for (i = 0; i < TABLEHEIGHT; i++)
	{
		NewTable[i] = new float[TABLEWIDTH + TABLEHEIGHT - 1];
		for (j = 0; j < TABLEWIDTH + TABLEHEIGHT - 1; j++)
		{
			NewTable[i][j] = 0;
		}
	}

	for (i = 0; i < TABLEHEIGHT; i++)
	{
		for (j = 0; j < TABLEWIDTH + TABLEHEIGHT - 1; j++)
		{
			if (i != *ResolutionI - 1)
			{
				float aij = Table[i][j];
				float airjr = Table[*ResolutionI - 1][*ResolutionJ - 1];
				float airj = Table[*ResolutionI - 1][j];
				float aijr = Table[i][*ResolutionJ - 1];
				float result = (aij * airjr - airj * aijr) / airjr;
				//cout << "a[" << i + 1 << "," << j + 1 << "] = (" << aij << " * " << airjr << " - " << airj << " * " << aijr << ") / " << airjr << " = " << result << endl;
				NewTable[i][j] = result;
			}
			else
			{
				if (i != TABLEHEIGHT - 1)
				{
					float aij = Table[i][j];
					float airjr = Table[*ResolutionI - 1][*ResolutionJ - 1];
					float result = aij / airjr;
					//cout << "a[" << i + 1 << "," << j + 1 << "] " << aij << " / " << airjr << " = " << result << endl;
					NewTable[i][j] = result;
				}
				else
				{
					NewTable[i][j] = Table[i][j];
				}
			}
		}
	}
	cout << endl;
	return NewTable;
}

bool IsTableSolved(float **Table)
{
	for (int j = 0; j < TABLEWIDTH; j++)
	{
		if (Table[TABLEHEIGHT - 1][j] < 0)
			return false;
	}
	return true;
}

int main()
{
	int i;
	string Rows[TABLEHEIGHT - 1];
	/*
	string B = "32, 20, 1800";
	string C = "50, 70, 50, 135, 80, 50";
	Rows[0] = "10, 2, 3, 2, 4, 5";
	Rows[1] = "1, 2, 3, 2, 1, 5";
	Rows[2] = "200, 100, 300, 300, 100, 400";
	*/
	/*
	string B = "76, 70, 4270";
	string C = "430, 165, 525, 315, 380, 205, 400";
	Rows[0] = "2, 9, 7, 6, 5, 4, 9";
	Rows[1] = "4, 3, 5, 2, 7, 6, 5";
	Rows[2] = "360, 125, 475, 250, 350, 120, 375";
	*/
	
	string B = "55, 73, 7000";
	string C = "1000, 600, 150, 1100, 700, 800, 300";
	Rows[0] = "4, 2, 3, 5, 2, 6, 4";
	Rows[1] = "5, 7, 2, 6, 7, 6, 3";
	Rows[2] = "700, 400, 100, 800, 500, 600, 200";
	
	/*
	string B = "100, 500, 500"; 
	Rows[0] = "3, 4, 5, 4, 7, 2, 4";
	Rows[1] = "20, 45, 10, 20, 20, 15, 35";
	Rows[2] = "15, 13, 12, 21, 14, 10, 15";
	string C = "20, 18, 16, 28, 20, 13, 20";
	*/
	setlocale(LC_ALL, "RUS");

	float **Table = ConvertToTable(Rows, &B, &C);
	float **OriginalTable = ConvertToTable(Rows, &B, &C);
	cout << "Массы товаров равны " << Rows[0] << ", максимальная масса равна " << Table[0][TABLEWIDTH + TABLEHEIGHT - 2] << endl;
	cout << "Объемы товаров равны " << Rows[1] << ", объем ранца равен " << Table[1][TABLEWIDTH + TABLEHEIGHT - 2] << endl;
	cout << "Закупочные цены товаров равны " << Rows[2] << ", коробейник может закупить товаров на сумму не более чем " << Table[2][TABLEWIDTH + TABLEHEIGHT - 2] << endl;
	cout << "Ожидаемая прибыль с товара: " << C << endl;

	cout << endl << "Модель данной задачи имеет вид:" << endl;
	cout << "Найти числа ";
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		cout << "x" << i + 1;
		if (i < TABLEWIDTH - 2)
			cout << ", ";

	}
	cout << ", удовлетворяющие условиям" << endl;
	for (i = 0; i < 3; i++)
	{
		cout << "	";
		for (int j = 0; j < TABLEWIDTH - 1; j++)
		{
			cout << Table[i][j] << "x" << j + 1;
			if (j < TABLEWIDTH - 2)
			{
				cout << " + ";
			}
			else
			{
				cout << " <= " << Table[i][j + TABLEHEIGHT];
			}
		}
		cout << endl;
	}
	cout << " и " << endl;
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		cout << "	x" << i + 1 << " >= " << 0 << endl;
	}
	cout << endl;
	cout << "и доставляющие максимальное значение целевой функции " << endl;
	cout << "	fZ = ";
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		cout << Table[3][i] * -1 << "x" << i + 1;
		if (i < TABLEWIDTH - 2)
			cout << " + ";
	}
	cout << " -> max" << endl << endl;

	cout << "Каноническая модель примет вид: " << endl;
	cout << "Найти числа ";
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		cout << "x" << i + 1;
		if (i < TABLEWIDTH - 2)
			cout << ", ";

	}
	cout << ", удовлетворяющие условиям" << endl;
	for (i = 0; i < 3; i++)
	{
		cout << "	";
		for (int j = 0; j < TABLEWIDTH; j++)
		{
			if (j < TABLEWIDTH - 1)
			{
				cout << Table[i][j] << "x" << j + 1;
				cout << " + ";
			}
			else
			{
				if (j < TABLEWIDTH)
					cout << "x" << TABLEWIDTH + i << " = " << Table[i][j + TABLEHEIGHT - 1];
			}
		}
		cout << endl;
	}
	cout << " и " << endl;
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		cout << "	x" << i + 1 << " >= " << 0 << endl;
	}
	cout << endl;
	cout << "и доставляющие максимальное значение целевой функции " << endl;
	cout << "	fZ = ";
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		cout << Table[3][i] * -1 << "x" << i + 1;
		if (i < TABLEWIDTH - 2)
			cout << " + ";
	}
	cout << " -> max" << endl;

	cout << endl;
	while (!IsTableSolved(Table))
	{
		PrintTable(Table);
		cout << "min C < 0; План не оптимален, выполняем итерацию" << endl;
		int ResolutionI = 0, ResolutionJ = 0;
		FindResolutor(Table, &ResolutionI, &ResolutionJ);
		float **NewTable = ResolveTable(Table, &ResolutionI, &ResolutionJ);
		for (i = 0; i < TABLEHEIGHT; i++)
		{
			delete(Table[i]);
		}
		delete(Table);
		Table = NewTable;
	}
	PrintTable(Table);
	
	cout << "X = (";
	for (i = 0; i < TABLEWIDTH - 1 + 3; i++)
	{
		cout << Table[TABLEHEIGHT - 1][i];
		if (i < TABLEWIDTH + 1)
			cout << "; ";
	}
	cout << ") = " << Table[TABLEHEIGHT - 1][TABLEWIDTH - 1 + 3] << endl;
	cout << endl << "Таблица решена" << endl;

	int variables[TABLEHEIGHT - 1];
	int variablePositions[TABLEHEIGHT - 1];
	int variablesFound = 0;
	for (int j = 0; j < TABLEWIDTH - 1; j++)
	{
		bool validColumn = true;
		bool foundOne = false;
		int onePosition = 0;
		for (i = 0; i < TABLEHEIGHT - 1 && validColumn; i++)
		{
			if (Table[i][j] == 1 || Table[i][j] == 0)
			{
				if (Table[i][j] == 1)
				{
					if (!foundOne)
					{
						foundOne = true;
						onePosition = i;
					}
					else
					{
						validColumn = false;
					}
				}
			}
			else
			{
				validColumn = false;
			}
		}
		if (validColumn)
		{
			variables[variablesFound] = j;
			variablePositions[variablesFound] = onePosition;
			variablesFound++;
		}
	}

	/*for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		cout << variables[i] << "/" << variablePositions[i] << endl;
	}*/

	cout << "Найденный план оптимален" << endl;
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		cout << "Товар №" << variables[i] + 1 << " закупается в количестве " << (int)Table[i][TABLEWIDTH + TABLEHEIGHT - 2] << " единиц" << endl;
	}

	for (i = 0; i < TABLEHEIGHT; i++)
	{
		delete(Table[i]);
		delete(OriginalTable[i]);
	}
	delete(Table);
	delete(OriginalTable);
	return 0;
}