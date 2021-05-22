#include "pch.h"//Необязательный файл, зачем-то прикрепляется самой Visual Studio 2017
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>

#pragma warning(disable:4996)

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

const int TABLEWIDTH = 7;
const int TABLEHEIGHT = 3;

bool used_variables[TABLEWIDTH - 1];
int cookie_type_amount[TABLEWIDTH - 1];
int found_variables = 0;

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
			if (!used_variables[j - 1])
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
							cout << "|     T" << to_string(j);
						}
						else
						{
							cout << "|      B|" << endl;
						}
					}
				}
				else
				{
					if (j > 0)
					{
						int symbols = 7;
						string numToPrint = to_string(Table[i - 1][j - 1]);
						if (numToPrint.length() > symbols)
						{
							numToPrint = numToPrint.substr(0, symbols - 1);
						}
						string Spaces = "";
						for (int k = 0; k < 7 - numToPrint.length(); k++)
						{
							Spaces += " ";
						}
						cout << "|" << Spaces << numToPrint;
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
			if (j == TABLEWIDTH + TABLEHEIGHT - 1)
			{
				cout << "|" << endl;
			}
		}
	}
	cout << endl;
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
		if (Table[TABLEHEIGHT - 1][j] < min && !used_variables[j])
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
			if (!used_variables[j])
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

string RoundFloatNumber(float n)
{
	string s = to_string(n);
	string ns;
	for (int i = 0; i < s.length() && s[i] != ','; i++)
	{
		ns += s[i];
	}
	return ns;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int i;
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		used_variables[i] = false;
		cookie_type_amount[i] = 0;
	}
	int largestWeight = 0;
	string Rows[TABLEHEIGHT - 1];
	/*int startWeight = 100000;
	int startMoney = 16000;
	Rows[0] = "200, 200, 500, 500, 1000, 1000";//Веса
	Rows[1] = "25, 27, 60, 65, 105, 110";//Закупочные цены
	string C = "5, 6, 10, 10, 25, 30";//Прибыль
	string minAmountsS = "75, 100, 25, 30, 10, 10";//Минимальные объемы закупок
	string maxAmountsS = "130, 160, 40, 50, 15, 15";//Максимальные объемы закупок
	string B = "0, 0";*/
	
	int startWeight = 300000;
	int startMoney = 25000;
	Rows[0] = "200, 200, 200, 1000, 1000, 1000";
	Rows[1] = "15, 18, 13, 60, 75, 55";
	//string C = "25, 30, 20, 100, 125, 85";
	string C = "10, 12, 7, 40, 50, 30";//Для удобства вычисления строка Розничные цены заменена на строку Прибыль
	string minAmountsS = "125, 150, 100, 40, 50, 30";
	string maxAmountsS = "250, 300, 200, 80, 100, 60";
	string B = "0, 0";
	
	int weight = startWeight;
	int money = startMoney;
	int Mmin = 0, Smin = 0;
	int minAmounts[TABLEWIDTH - 1];
	int maxAmounts[TABLEWIDTH - 1];

	vector<string> minAmountsSV = Split(minAmountsS);
	vector<string> maxAmountsSV = Split(maxAmountsS);
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		minAmounts[i] = stoi(minAmountsSV[i]);
		maxAmounts[i] = stoi(maxAmountsSV[i]);
	}

	float **OriginalTable = ConvertToTable(Rows, &B, &C);
	
	while (weight > largestWeight)
	{		
		largestWeight = -1; /*OriginalTable[0][0];*///Нахождение веса самой тяжелой еще не распределенной пачки
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (OriginalTable[0][i] > largestWeight && !used_variables[i])
			{
				largestWeight = OriginalTable[0][i];
			}
		}
		float **Table = ConvertToTable(Rows, &B, &C);

		cout << "Найти числа ";
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (!used_variables[i])
			{
				cout << " x" << i + 1;
				if (i < TABLEWIDTH - 2)
					cout << ",";
			}
		}
		cout << ", удовлетворяющие условиям:" << endl;
		cout << "(1)	";
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (!used_variables[i])
			{
				cout << Table[0][i] << "*X" << i + 1;
				if (i < TABLEWIDTH -1 - found_variables)
					cout << " + ";
			}
		}
		cout << "<=" << weight << endl;

		cout << "	";
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (!used_variables[i])
			{
				cout << Table[1][i] << "*X" << i + 1;
				if (i < TABLEWIDTH - 1 - found_variables)
					cout << " + ";
			}
		}
		cout << "<=" << money << endl;

		cout << "(2)";
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (cookie_type_amount[i] > 0)
			{
				cout << "	X" << i + 1 << "* = " << cookie_type_amount[i] << endl;
			}
			else
			{
				cout << "	" << minAmounts[i] << " <= X" << i + 1 << " <= " << maxAmounts[i] << endl;
			}
		}
		cout << endl;

		cout << "(3)";
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			cout << "	X" << i + 1 << " C Z" << endl;
		}
		cout << endl;

		cout << "и доставляющие максимальное значение целевой функции" << endl << "	fZ = ";
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (!used_variables[i])
			{
				cout << (-1)*Table[2][i] << "*X" << i + 1;
				if (i < TABLEWIDTH - 1 - found_variables)
					cout << " + ";
			}
		}
		cout << "=> max" << endl << endl;
		if (weight == startWeight)
		{
			cout << "Произведем закупку минимальных объемов товара" << endl;
			string MminS = "", SminS = "";
			for (i = 0; i < TABLEWIDTH - 1; i++)
			{
				Mmin += Table[0][i] * minAmounts[i];
				MminS += RoundFloatNumber(Table[0][i]);
				MminS += "*";
				MminS += RoundFloatNumber(minAmounts[i]);
				if (i < TABLEWIDTH - 2)
					MminS += " + ";
				Smin += Table[1][i] * minAmounts[i];
				SminS += RoundFloatNumber(Table[1][i]);
				SminS += "*";
				SminS += RoundFloatNumber(minAmounts[i]);
				if (i < TABLEWIDTH - 2)
					SminS += " + ";
			}
			cout << "Mmin = " << MminS << " = " << Mmin << endl;
			cout << "Smin = " << SminS << " = " << Smin << endl;

			weight -= Mmin;//Сделали минимальные закупки
			money -= Smin;

			cout << "Минимальные потребности в товарах требуют " << Mmin << " граммов и " << Smin << " рублей" << endl;
			cout << "Осталось " << weight << " граммов и " << money << " рублей" << endl << endl;
		}

		Table[0][TABLEWIDTH + 1] = weight;
		Table[1][TABLEWIDTH + 1] = money;

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
		cout << endl << "План оптимален" << endl;
		int variables[TABLEWIDTH - 1];
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			variables[i] = -1;
		}
		for (int j = 0; j < TABLEWIDTH - 1; j++)
		{
			if (!used_variables[j])
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
					variables[onePosition] = j;
				}
			}
		}
		int checkedVariables = 0;
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (variables[i] != -1)
			{
				used_variables[variables[i]] = true;//Переменная отмечается как использованная и в дальнейшем не используется в расчетах
				int usedWeight = 0, usedMoney = 0, cookiesBought = 0;
				if (Table[checkedVariables][TABLEWIDTH + 1] <= maxAmounts[variables[i]])//Нахождение максимального количества товара
				{
					int additionalCookies = 0;
					cookiesBought = Table[checkedVariables][TABLEWIDTH + 1] + minAmounts[variables[i]];
					cout << "Из плана следует, что нужно закупить еще " << Table[checkedVariables][TABLEWIDTH + 1] << " пачек печенья, суммарно получив " << cookiesBought << " пачек" << endl;
					if (cookiesBought > maxAmounts[variables[i]])
					{
						additionalCookies = maxAmounts[variables[i]] - minAmounts[variables[i]];
						cookiesBought = maxAmounts[variables[i]];
						cout << "Максимальное количество этого товара составляет " << maxAmounts[variables[i]] << ", причем " << minAmounts[variables[i]] << " уже закуплено, соответственно мы можем закупить только " << cookiesBought << " пачек печенья X" << variables[i] + 1 << endl;
					}
					else
						additionalCookies = Table[checkedVariables][TABLEWIDTH + 1];
					cookie_type_amount[variables[i]] = cookiesBought;
					usedWeight = additionalCookies * OriginalTable[0][variables[i]];
					usedMoney = additionalCookies * OriginalTable[1][variables[i]];
					cout << "На дополнительные " << additionalCookies << " пачек печенья нам потребуется " << usedWeight << " грамм веса и " << usedMoney << " рублей" << endl;
				}
				else
				{
					cout << "Из плана следует, что нужно закупить дополнительно " << Table[checkedVariables][TABLEWIDTH + 1] << " пачек печенья X" << variables[i] + 1 << ", но мы можем закупить не более " << maxAmounts[variables[i]] << " пачек печенья. Закупаем максимальное количество и удаляем переменную из модели." << endl;
					cookie_type_amount[variables[i]] = maxAmounts[variables[i]];
					cookiesBought = cookie_type_amount[variables[i]] - minAmounts[variables[i]];
					usedWeight = cookiesBought * OriginalTable[0][variables[i]];
					usedMoney = cookiesBought * OriginalTable[1][variables[i]];
					cout << "На дополнительные " << cookiesBought << " пачек печенья нам потребуется " << usedWeight << " грамм веса и " << usedMoney << " рублей" << endl;
				}
				cout << "X" << variables[i] + 1 << "* = " << cookie_type_amount[variables[i]] << endl;
				weight -= usedWeight;
				money -= usedMoney;
				cout << "Остается " << weight << " г нераспределенного веса и " << money << " рублей" << endl;
				checkedVariables++;
				found_variables++;
			}
		}
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			//cout << "|" << cookie_type_amount[i] << "|" << endl;
		}
		if (weight > largestWeight)
		{
			for (i = 0; i < TABLEHEIGHT; i++)
			{
				delete(Table[i]);
			}
			delete(Table);
		}
	}
	
	if (weight == 0)
	{
		int sumM=0, sumS=0;
		cout << "Не осталось нераспределенного веса, имеем план" << endl<<"X = (";
		for (i = 0; i < TABLEWIDTH-1; i++)
		{
			if (cookie_type_amount[i] > 0)
			{
				cout << cookie_type_amount[i];
			}
			else
			{
				cout << minAmounts[i];
			}
			if (i < TABLEWIDTH - 2)
			{
				cout << ",";
			}
			else
			{
				cout << ")" << endl;
			}
		}
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (cookie_type_amount[i] > 0)
			{
				cout << cookie_type_amount[i] << " * " << OriginalTable[0][i];
				sumM += cookie_type_amount[i] * OriginalTable[0][i];
			}
			else
			{
				cout << minAmounts[i] << " * " << OriginalTable[0][i];
				sumM += minAmounts[i] * OriginalTable[0][i];
			}
			if (i < TABLEWIDTH - 2)
			{
				cout << " + ";
			}
			else
			{
				cout << " = ";
			}
		}
		cout << sumM << endl;
		if (sumM <= startWeight)
		{
			cout << "Используемый вес не превышает предела в " << startWeight << endl;
		}
		else
		{
			cout << "Используемый вес, однако, неким непостижимым образом, предел превышает" << endl;
		}
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (cookie_type_amount[i] > 0)
			{
				cout << cookie_type_amount[i] << " * " << OriginalTable[1][i];
				sumS += cookie_type_amount[i] * OriginalTable[1][i];
			}
			else
			{
				cout << minAmounts[i] << " * " << OriginalTable[1][i];
				sumS += minAmounts[i] * OriginalTable[1][i];
			}
			if (i < TABLEWIDTH - 2)
			{
				cout << " + ";
			}
			else
			{
				cout << " = ";
			}
		}
		cout << sumS << endl;
		if (sumS <= startWeight)
		{
			cout << "Расходумые деньги не превышают предела в " << startMoney << endl;
		}
		else
		{
			cout << "Расходуемые деньги почему-то больше бюджета. Придется брать кредит под 22%!" << endl;
		}
	}
	else
	{
		cout << "Осталось " << weight << " г нераспределенного веса и " << money << " рублей, так как оставшийся вес слишком маленький (меньше самой большой упаковкой весом в " << largestWeight << " г). Это уже ручками дорешивать." << endl;
		/*int possibleWeights[TABLEWIDTH - 1];
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			possibleWeights[i] = 0;
			if (weight <= OriginalTable[0][i])
			{
				possibleWeights[i] = weight;
			}
		}*/
	}
	for (i = 0; i < TABLEHEIGHT; i++)
	{
		delete(OriginalTable[i]);
	}
	delete(OriginalTable);

	return 0;
}