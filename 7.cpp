#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

const int TABLEWIDTH = 7;
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
			if (min > a)
			{
				min = a;
				*ResolutionI = i + 1;
			}
		}
	}
	cout << "Минимальное число равно " << min << endl;	
	cout << "Резолютор равен " << Table[*ResolutionI - 1][*ResolutionJ - 1] << " и находится на позиции [" << *ResolutionI << "," << *ResolutionJ << "]" << endl;
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
				cout << "a[" << i + 1 << "," << j + 1 << "] = (" << aij << " * " << airjr << " - " << airj << " * " << aijr << ") / " << airjr << " = " << result << endl;
				NewTable[i][j] = result;
			}
			else
			{
				if (i != TABLEHEIGHT - 1)
				{
					float aij = Table[i][j];
					float airjr = Table[*ResolutionI - 1][*ResolutionJ - 1];
					float result = aij / airjr;
					cout << "a[" << i + 1 << "," << j + 1 << "] " << aij << " / " << airjr << " = " << result << endl;
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

	string B = "22, 19, 22";
	string C = "50, 100, 60, 160, 75, 65";
	Rows[0] = "3, 2, 4, 1, 1, 4";
	Rows[1] = "2, 1, 1, 2, 1, 2";
	Rows[2] = "2, 1, 2, 3, 1, 3";
	setlocale(LC_ALL, "RUS");
	float **Table = ConvertToTable(Rows, &B, &C);
	float **OriginalTable = ConvertToTable(Rows, &B, &C);
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
	cout << "Первый план" << endl;
	cout << "A = (";
	for (i = 0; i < TABLEWIDTH - 1 + 3; i++)
	{
		cout << Table[TABLEHEIGHT - 1][i];
		if (i < TABLEWIDTH + 1)
			cout << "; ";
	}
	cout << ") = " << Table[TABLEHEIGHT - 1][TABLEWIDTH - 1 + 3] << endl;

	float Z = 0;
	int j = 0;
	cout << "Второй план" << endl;
	cout << "Z = ";
	for (i = 0; i < TABLEWIDTH - 1 + 3; i++)
	{
		if (Table[TABLEHEIGHT - 1][i] == 0)
		{
			cout << -1 * OriginalTable[TABLEHEIGHT - 1][i] << "*" << Table[j][TABLEWIDTH - 1 + 3];
			if (j < TABLEHEIGHT - 2)
				cout << " + ";
			Z += -1 * OriginalTable[TABLEHEIGHT - 1][i] * Table[j][TABLEWIDTH - 1 + 3];
			j++;
		}
	}
	cout << " = " << Z << endl;
	cout << endl << "Таблица решена" << endl;
	for (i = 0; i < TABLEHEIGHT; i++)
	{
		delete(Table[i]);
		delete(OriginalTable[i]);
	}
	delete(Table);
	delete(OriginalTable);
	return 0;
}