#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

const int TABLEWIDTH = 5;
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
	delete(str);
	delete(ptr);
	return items;
}

double **ConvertToTable(string *Rows, string *B, string *C)
{
	int i, j;
	double **NewTable = 0;
	NewTable = new double*[TABLEHEIGHT];

	for (i = 0; i < TABLEHEIGHT; i++)
	{
		NewTable[i] = new double[TABLEWIDTH];
	}

	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		vector<string> numbers = Split(Rows[i]);
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			NewTable[i][j] = stod(numbers[j]);
			//cout << NewTable[i][j] << " ";
		}
		//cout << endl;
	}

	vector<string> Bs = Split(*B);
	for (i = 0; i < TABLEHEIGHT; i++)
	{
		NewTable[i][TABLEWIDTH - 1] = stod(Bs[i]);
		//cout << NewTable[i][TABLEWIDTH - 1] << " ";
	}
	//cout << endl;

	vector<string> Cs = Split(*C);
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		NewTable[TABLEHEIGHT - 1][i] = stof(Cs[i]);
		//cout << NewTable[TABLEHEIGHT - 1][i] << " ";
	}
	//cout << NewTable[TABLEHEIGHT - 1][TABLEWIDTH - 1] << endl;
	return NewTable;
}

void PrintTable(double **Table)
{
	int i, j;
	for (i = 0; i < TABLEHEIGHT + 1; i++)
	{
		for (j = 0; j < TABLEWIDTH + 1; j++)
		{
			if (i == 0)
			{
				if (j == 0)
					cout << "|Станция|";
				else
				{
					if (j < TABLEWIDTH)
						cout << "B" << j << "	|";
					else
						cout << "Запасы	|";
				}
			}
			else
			{
				if (j == 0)
				{
					if (i < TABLEHEIGHT)
					{
						cout << "|A" << i << "	|";
					}
					else
					{
						cout << "|Вм-сть |";
					}
				}
				else
				{
					cout << Table[i-1][j-1] << "	|";
				}
			}
			if (j == TABLEWIDTH)
				cout << endl;
		}
	}
}

void PrintTablePlan(double **Table, double **x)
{
	int i, j;
	cout << "-------------------------------------------------" << endl;
	for (i = 0; i < TABLEHEIGHT * 2; i++)
	{
		for (j = 0; j < TABLEWIDTH + 1; j++)
		{
			if (i == 0)
			{
				if (j == 0)
					cout << "|Станция|";
				else
				{
					if (j < TABLEWIDTH)
					{
						cout << "B" << j << "	|";
					}
					else
					{
						cout << "Запасы	|";
					}
				}
			}
			else
			{
				if (j == 0)
				{
					if (i < TABLEHEIGHT * 2 - 1)
					{
						if (i % 2 == 1)
							cout << "|A" << i / 2 + 1 << "	|";
						else
							cout << "|	";
					}
					else
					{
						cout << "|Вм-сть |";
					}
				}
				else
				{
					if (i < TABLEHEIGHT * 2 - 1)
					{
						if (i % 2 == 0)
						{
							if (Table[i / 2 - 1][j - 1] <= 0)
								cout << "|   " << "-";
							else
								cout << "|   " << Table[i / 2 - 1][j - 1];
							if (j == TABLEWIDTH)
								cout << "	|";
							else
								cout << "	";
						}
						else
						{
							if (j < TABLEWIDTH)
							{
								if (x[i / 2][j - 1] <= 0)
									cout << "-" << "	|";
								else
									cout << x[i / 2][j - 1] << "	|";
							}
							else
							{
								cout << "	|";
							}
						}
					}
					else
					{
						cout << Table[TABLEHEIGHT - 1][j - 1] << "	|";
					}
				}
			}
			if (j == TABLEWIDTH)
				cout << endl;
		}
	}
	cout << "-------------------------------------------------" << endl;
}

void PrintTablePlan(double **Table, double **x, double *u, double *v)
{
	int i, j;
	cout << "-------------------------------------------------" << endl;
	for (i = 0; i < TABLEHEIGHT * 2-1; i++)
	{
		for (j = 0; j < TABLEWIDTH; j++)
		{
			if (i == 0)
			{
				if (j == 0)
					cout << "|	|";
				else
				{
					if (j < TABLEWIDTH)
					{
						cout << "v" << j << "=" << v[j-1] << "	|";
					}
				}
			}
			else
			{
				if (j == 0)
				{
					if (i < TABLEHEIGHT * 2 - 1)
					{
						if (i % 2 == 1)
							cout << "|u" << i / 2 + 1 << "=" << u[i / 2] << "	|";
						else
							cout << "|	";
					}
					else
					{
						cout << "|	|";
					}
				}
				else
				{
					if (i < TABLEHEIGHT * 2 - 1)
					{
						if (i % 2 == 0)
						{
							if (Table[i / 2 - 1][j - 1] <= 0)
								cout << "|   " << "-";
							else
								cout << "|   " << Table[i / 2 - 1][j - 1];
							if (j == TABLEWIDTH)
								cout << "	|";
							else
								cout << "	";
						}
						else
						{
							if (j < TABLEWIDTH)
							{
								if (x[i / 2][j - 1] <= 0)
									cout << "-" << "	|";
								else
									cout << x[i / 2][j - 1] << "	|";
							}
							else
							{
								cout << "	|";
							}
						}
					}
					else
					{
						cout << Table[TABLEHEIGHT - 1][j - 1] << "	|";
					}
				}
			}
			if (j == TABLEWIDTH-1)
				cout << endl;
		}
	}
	cout << "-------------------------------------------------" << endl;
}

void PrintTablePlan(double **Table, double **x, double **prefs)
{
	int i, j;
	cout << "-------------------------------------------------" << endl;
	for (i = 0; i < TABLEHEIGHT * 2; i++)
	{
		for (j = 0; j < TABLEWIDTH + 1; j++)
		{
			if (i == 0)
			{
				if (j == 0)
					cout << "|Станция|";
				else
				{
					if (j < TABLEWIDTH)
					{
						cout << "B" << j << "	|";
					}
					else
					{
						cout << "Запасы	|";
					}
				}
			}
			else
			{
				if (j == 0)
				{
					if (i < TABLEHEIGHT * 2 - 1)
					{
						if (i % 2 == 1)
							cout << "|A" << i / 2 + 1 << "	|";
						else
							cout << "|	";
					}
					else
					{
						cout << "|Вм-сть |";
					}
				}
				else
				{
					if (i < TABLEHEIGHT * 2 - 1)
					{
						if (i % 2 == 0)
						{
							if (Table[i / 2 - 1][j - 1] <= 0)
								cout << "|   " << "-";
							else
								cout << "|   " << Table[i / 2 - 1][j - 1];
							if (j == TABLEWIDTH)
								cout << "	|";
							else
								cout << "	";
						}
						else
						{
							if (j < TABLEWIDTH)
							{
								if (x[i / 2][j - 1] <= 0)
									cout << "-" << "	|";
								else
								{
									cout << x[i / 2][j - 1];
									for (int k = 0; k < prefs[i/2][j-1]; k++)
									{
										cout << "V";
									}
									cout << "	|";
								}
							}
							else
							{
								cout << "	|";
							}
						}
					}
					else
					{
						cout << Table[TABLEHEIGHT - 1][j - 1] << "	|";
					}
				}
			}
			if (j == TABLEWIDTH)
				cout << endl;
		}
	}
	cout << "-------------------------------------------------" << endl;
}

bool Depleted(double **Table)
{
	for (int i = 0; i < TABLEHEIGHT - 1; i++)
	{
		if (Table[i][TABLEWIDTH - 1] > 0)
			return false;
	}
	for (int i = 0; i < TABLEWIDTH - 1; i++)
	{
		if (Table[TABLEHEIGHT - 1][i] > 0)
			return false;
	}
	return true;
}

void CopyTable(double **src, double **dest)
{
	int i, j;
	for (i = 0; i < TABLEHEIGHT; i++)
	{
		for (j = 0; j < TABLEWIDTH; j++)
		{
			dest[i][j] = src[i][j];
		}
	}
}

double NorthWestPlan(double **Table, double **x)
{
	cout << "[Северозападный план]" << endl;
	double Z = 0;
	int i, j;
	int row = 0, column = 0;
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			Table[i][j] = 0;
		}
	}
	PrintTablePlan(Table, x);
	while (!Depleted(Table))
	{
		if (Table[row][TABLEWIDTH - 1] > Table[TABLEHEIGHT - 1][column])
		{
			Table[row][column] = Table[TABLEHEIGHT - 1][column];
			cout << Table[row][TABLEWIDTH - 1] << " - " << Table[TABLEHEIGHT - 1][column] << " = " << Table[row][TABLEWIDTH - 1] - Table[TABLEHEIGHT - 1][column] << endl;
			Table[row][TABLEWIDTH - 1] -= Table[TABLEHEIGHT - 1][column];
			Table[TABLEHEIGHT - 1][column] = 0;			
			column++;
		}
		else
		{
			Table[row][column] = Table[row][TABLEWIDTH - 1];
			cout << Table[TABLEHEIGHT - 1][column] << " - " << Table[row][TABLEWIDTH - 1] << " = " << Table[TABLEHEIGHT - 1][column] - Table[row][TABLEWIDTH - 1]<<endl;
			Table[TABLEHEIGHT - 1][column] -= Table[row][TABLEWIDTH - 1];
			Table[row][TABLEWIDTH - 1] = 0;
			row++;
		}
	}
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			if (Table[i][j] > 0)
				Z += x[i][j] * Table[i][j];
		}
	}
	PrintTablePlan(Table, x);
	return Z;
}

double MinimalPlan(double **Table, double **x)
{
	cout << "[Минимальный план]" << endl;
	double Z = 0;
	int i, j;
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			Table[i][j] = 0;
		}
	}
	int lastmin = -1;
	PrintTablePlan(Table, x);
	while (!Depleted(Table))
	{
		int min = x[0][0];
		int minr = 0, minc = 0;
		for (i = 0; i < TABLEHEIGHT - 1; i++)
		{
			for (j = 0; j < TABLEWIDTH - 1; j++)
			{
				if (x[i][j] < min && x[i][j] > 0)
				{
					if (x[i][j] > lastmin || lastmin == -1)
					{
						min = x[i][j];
						minr = i;
						minc = j;
					}
				}
			}
		}
		lastmin = min;
		if (Table[minr][TABLEWIDTH - 1] > Table[TABLEHEIGHT - 1][minc])
		{
			Table[minr][minc] = Table[TABLEHEIGHT - 1][minc];
			cout << Table[minr][TABLEWIDTH - 1] << " - " << Table[TABLEHEIGHT - 1][minc] << " = " << Table[minr][TABLEWIDTH - 1] - Table[TABLEHEIGHT - 1][minc] << endl;
			Table[minr][TABLEWIDTH - 1] -= Table[TABLEHEIGHT - 1][minc];
			Table[TABLEHEIGHT - 1][minc] = 0;
		}
		else
		{
			Table[minr][minc] = Table[minr][TABLEWIDTH - 1];
			cout << Table[TABLEHEIGHT - 1][minc] << " - " << Table[minr][TABLEWIDTH - 1] << " = " << Table[TABLEHEIGHT - 1][minc] - Table[minr][TABLEWIDTH - 1] << endl;
			Table[TABLEHEIGHT - 1][minc] -= Table[minr][TABLEWIDTH - 1];
			Table[minr][TABLEWIDTH - 1] = 0;
		}
	}
	PrintTablePlan(Table, x);
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			if (Table[i][j] > 0)
				Z += x[i][j] * Table[i][j];
		}
	}
	return Z;
}

bool PreferencesLeft(double **prefs)
{
	int i, j;
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			if (prefs[i][j] > 0)
			{
				return true;
			}
		}
	}
	return false;
}

void FindSmallestPreference(double **x, double **prefs, int type, int *r, int *c)
{
	int i, j;
	int min = -1;
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			if (prefs[i][j] == type)
			{
				if (min == -1 || min > x[i][j])
				{
					min = x[i][j];
					*r = i;
					*c = j;
				}
			}
		}
	}
}

bool DoublePreferencesLeft(double **prefs)
{
	int i, j;
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			if (prefs[i][j] == 2)
			{
				return true;
			}
		}
	}
	return false;
}

double DoublePreferencePlan(double **Table, double **x)
{
	cout << "[План двойного предпочтения]" << endl;
	double Z = 0;
	int i, j;
	double **preferences = new double*[TABLEHEIGHT-1];
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		preferences[i] = new double[TABLEWIDTH-1];
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			Table[i][j] = 0;
			preferences[i][j] = 0;
		}
	}
	
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		int min = x[i][0];
		int minc = 0;
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			if (x[i][j] < min)
			{
				min = x[i][j];
				minc = j;
			}
		}
		preferences[i][minc]++;
	}
	
	for (j = 0; j < TABLEWIDTH - 1; j++)
	{
		int min = x[0][j];
		int minr = 0;
		for (i = 0; i < TABLEHEIGHT - 1; i++)
		{
			if (x[i][j] < min)
			{
				min = x[i][j];
				minr = i;
			}
		}
		preferences[minr][j]++;
	}

	PrintTablePlan(Table, x, preferences);
	int row, column;
	while (PreferencesLeft(preferences))
	{
		if (DoublePreferencesLeft(preferences))
		{
			FindSmallestPreference(x, preferences, 2, &row, &column);
		}
		else
		{
			FindSmallestPreference(x, preferences, 1, &row, &column);
		}

		preferences[row][column] = 0;
		if (Table[row][TABLEWIDTH - 1] > Table[TABLEHEIGHT - 1][column])
		{
			Table[row][column] = Table[TABLEHEIGHT - 1][column];
			cout << Table[row][TABLEWIDTH - 1] << " - " << Table[TABLEHEIGHT - 1][column] << " = " << Table[row][TABLEWIDTH - 1] - Table[TABLEHEIGHT - 1][column] << endl;
			Table[row][TABLEWIDTH - 1] -= Table[TABLEHEIGHT - 1][column];
			Table[TABLEHEIGHT - 1][column] = 0;
		}
		else
		{
			Table[row][column] = Table[row][TABLEWIDTH - 1];
			cout << Table[TABLEHEIGHT - 1][column] << " - " << Table[row][TABLEWIDTH - 1] << " = " << Table[TABLEHEIGHT - 1][column] - Table[row][TABLEWIDTH - 1] << endl;
			Table[TABLEHEIGHT - 1][column] -= Table[row][TABLEWIDTH - 1];
			Table[row][TABLEWIDTH - 1] = 0;
		}
	}
	PrintTablePlan(Table, x, preferences);
				
	while (!Depleted(Table))
	{
		int min = -1;
		for (i = 0; i < TABLEHEIGHT - 1; i++)
		{
			for (j = 0; j < TABLEWIDTH - 1; j++)
			{
				if (Table[i][j] == 0)
				{
					if (Table[i][TABLEWIDTH - 1] > 0 && Table[TABLEHEIGHT - 1][j] > 0)
					{
						if (min == -1 || min > x[i][j])
						{
							Table[i][j] = 0;
							min = x[i][j];
							row = i;
							column = j;
						}
					}
				}
			}
		}
		if (Table[row][TABLEWIDTH - 1] > Table[TABLEHEIGHT - 1][column])
		{
			Table[row][column] = Table[TABLEHEIGHT - 1][column];
			cout << Table[row][TABLEWIDTH - 1] << " - " << Table[TABLEHEIGHT - 1][column] << " = " << Table[row][TABLEWIDTH - 1] - Table[TABLEHEIGHT - 1][column] << endl;
			Table[row][TABLEWIDTH - 1] -= Table[TABLEHEIGHT - 1][column];
			Table[TABLEHEIGHT - 1][column] = 0;
		}
		else
		{
			Table[row][column] = Table[row][TABLEWIDTH - 1];
			cout << Table[TABLEHEIGHT - 1][column] << " - " << Table[row][TABLEWIDTH - 1] << " = " << Table[TABLEHEIGHT - 1][column] - Table[row][TABLEWIDTH - 1] << endl;
			Table[TABLEHEIGHT - 1][column] -= Table[row][TABLEWIDTH - 1];
			Table[row][TABLEWIDTH - 1] = 0;
		}
	}
	PrintTablePlan(Table, x);

	for (i = 0; i < TABLEHEIGHT-1; i++)
	{
		delete(preferences[i]);
	}
	delete(preferences);
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			if (Table[i][j] > 0)
				Z += x[i][j] * Table[i][j];
		}
	}
	return Z;
}

double minnum(double n1, double n2, double n3)
{
	if (n1 <= n2 && n1 <= n3)
		return n1;
	if (n2 <= n1 && n2 <= n3)
		return n2;
	if (n3 <= n1 && n3 <= n2)
		return n3;
	return n1;
}

bool UVDefined(double *u, double *v)
{
	int i, j;
	for (j = 0; j < TABLEWIDTH - 1; j++)
	{
		if (v[j] == 0)
			return false;
	}
	for (i = 1; i < TABLEHEIGHT - 1; i++)
	{
		if (u[j] == 0)
			return false;
	}
	return true;
}

int main()
{
	int i, j;
	setlocale(LC_ALL, "RUS");
	string Rows[TABLEHEIGHT - 1];
	string B = "90, 180, 130, 400";
	string C = "70, 120, 105, 105";
	Rows[0] = "14, 8, 17, 5";
	Rows[1] = "21, 10, 7, 11";
	Rows[2] = "3, 5, 8, 4";
	double **Table = ConvertToTable(Rows, &B, &C);
	double **OriginalTable, **NWPlan, **MinPlan, **DoublePlan, **x;
	double Znw, Zmin, Zdbp;
	PrintTable(Table);
	cout << endl;

	OriginalTable = new double*[TABLEHEIGHT];
	NWPlan = new double*[TABLEHEIGHT];
	MinPlan = new double*[TABLEHEIGHT];
	DoublePlan = new double*[TABLEHEIGHT];
	x = new double*[TABLEHEIGHT];
	for (i = 0; i < TABLEHEIGHT; i++)
	{
		OriginalTable[i] = new double[TABLEWIDTH];
		NWPlan[i] = new double[TABLEHEIGHT];
		MinPlan[i] = new double[TABLEHEIGHT];
		DoublePlan[i] = new double[TABLEHEIGHT];
		x[i] = new double[TABLEWIDTH];
	}

	CopyTable(Table, OriginalTable);
	CopyTable(Table, x);

	Znw = NorthWestPlan(Table, x);
	cout << "Z = " << Znw << endl << endl;
	CopyTable(Table, NWPlan);
	CopyTable(OriginalTable, Table);
	Zmin = MinimalPlan(Table, x);
	cout << "Z = " << Zmin << endl << endl;
	CopyTable(Table, MinPlan);
	CopyTable(OriginalTable, Table);
	Zdbp = DoublePreferencePlan(Table, x);
	CopyTable(Table, DoublePlan);
	cout << "Z = " << Zdbp << endl << endl;

	double minZ = minnum(Znw, Zmin, Zdbp);
	cout << "Минимальное Z = " << minZ << endl;
	double *u = new double[TABLEHEIGHT - 1];
	double *v = new double[TABLEWIDTH - 1];
	if (Znw == minZ)
	{
		CopyTable(NWPlan, Table);
	}
	else
	{
		if (Zmin == minZ)
		{
			CopyTable(MinPlan, Table);
		}
		else
		{
			CopyTable(DoublePlan, Table);
		}
	}

	/*
	for (j = 0; j < TABLEWIDTH - 1; j++)
	{
		v[j] = 0;
		for (i = 0; i < TABLEHEIGHT - 1; i++)
		{
			u[i] = 0;
			if (Table[i][j] > 0)
			{
				cout << "u" << i + 1 << " + v" << j + 1 << " = " << x[i][j] << endl;
			}
		}		
	}
	for (j = 0; j < TABLEWIDTH - 1; j++)
	{
		if (Table[0][j] > 0)
		{
			v[j] = x[0][j];
		}
	}
	PrintTablePlan(Table, x, u, v);
	*/

	for (i = 0; i < TABLEHEIGHT; i++)
	{
		//Выдает ошибку потому что C++ говно динозавра
		//delete(NWPlan[i]);
		//delete(MinPlan[i]);
		//delete(DoublePlan[i]);
		delete(OriginalTable[i]);
		delete(x[i]);
		delete(Table[i]);
	}
	delete(NWPlan);
	delete(MinPlan);
	delete(DoublePlan);
	delete(u);
	delete(v);
	delete(OriginalTable);
	delete(x);
	delete(Table);
	return 0;
}