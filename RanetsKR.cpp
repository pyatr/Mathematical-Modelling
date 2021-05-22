#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <algorithm>

#pragma warning(disable:4996)

using namespace std;

const int TABLEWIDTH = 8;
const int TABLEHEIGHT = 4;

bool used_variables[TABLEWIDTH - 1];
int item_type_amount[TABLEWIDTH - 1];
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
		{
			NewTable[i][TABLEWIDTH - 1 + i] = 1;
		}
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
							cout << "|      B";
						}
					}
				}
				else
				{
					if (j > 0)
					{
						int symbols = 7;
						string numToPrint;
						float num1 = Table[i - 1][j - 1];
						int num2 = Table[i - 1][j - 1];
						if (num1 - num2 == 0)
						{
							numToPrint = to_string(num2);
						}
						else
						{
							numToPrint = to_string(num1);
						}

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
			//else
			//	cout << endl << "====================================" << j << "====================================" << endl;
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
		item_type_amount[i] = 0;
	}
	int largestWeight = 0;
	string Rows[TABLEHEIGHT - 1];

	int startWeight = 1250;
	int startMoney = 9165;
	int startVolume = 500;
	Rows[0] = "30, 20, 15, 20, 10, 25, 35";//Масса
	Rows[1] = "5, 7, 11, 12, 14, 19, 22";//Объем
	Rows[2] = "120, 135, 175, 180, 195, 205, 275";//Закупочные цены
	//string C = "160, 195, 260, 270, 300, 315, 350";
	string C = "40, 60, 85, 90, 105, 110, 75";//Прибыль
	string minAmountsS = "2, 2, 2, 2, 2, 2, 2";
	string B = "0, 0, 0";

	int weight = startWeight;
	int money = startMoney;
	int volume = startVolume;
	int minAmounts[TABLEWIDTH - 1];

	vector<string> minAmountsSV = Split(minAmountsS);
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		minAmounts[i] = stoi(minAmountsSV[i]);
	}

	float **OriginalTable = ConvertToTable(Rows, &B, &C);

	while (weight > largestWeight || volume > startVolume)
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
				if (i < TABLEWIDTH - 1 - found_variables)
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
			if (item_type_amount[i] > 0)
			{
				cout << "	X" << i + 1 << "* = " << item_type_amount[i] << endl;
			}
			else
			{
				cout << "	" << minAmounts[i] << " <= X" << i + 1 << endl;
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
				cout << (-1)*Table[3][i] << "*X" << i + 1;
				if (i < TABLEWIDTH - 1 - found_variables)
					cout << " + ";
			}
		}
		cout << "=> max" << endl << endl;
		
		bool shouldBuyMinAmount=false;
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (minAmounts[i] > 0)
			{
				shouldBuyMinAmount = true;
			}
		}
		if (shouldBuyMinAmount && weight == startWeight)//Делаем закупки только один раз
		{
			cout << "Произведем минимальные закупки товаров" << endl;
			for (i = 0; i < TABLEWIDTH - 1; i++)
			{
				int usedWeight = 0, usedMoney = 0, usedVolume = 0;
				usedWeight = minAmounts[i] * OriginalTable[0][i];
				usedVolume = minAmounts[i] * OriginalTable[1][i];
				usedMoney = minAmounts[i] * OriginalTable[2][i];
				if (weight - usedWeight > 0 && money - usedMoney > 0 && volume - usedVolume > 0)
				{
					cout << "Закупаем товар X" << i + 1 << " в количестве " << minAmounts[i] << ", на что нам понадобится " << usedWeight << " ед. веса, " << usedVolume << " ед. объема и " << usedMoney << " рублей." << endl;
					weight -= usedWeight;
					volume -= usedVolume;
					money -= usedMoney;
				}
				item_type_amount[i] = minAmounts[i];
			}
		}

		cout << endl << "Имеем " << weight << " ед. нераспределенного веса, " << volume << " ед. нераспределенного объема и " << money << " рублей" << endl << endl;
		
		Table[0][TABLEWIDTH + TABLEHEIGHT - 2] = weight;
		Table[1][TABLEWIDTH + TABLEHEIGHT - 2] = volume;
		Table[2][TABLEWIDTH + TABLEHEIGHT - 2] = money;

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
		//int onePositions[TABLEWIDTH - 1];
		for (int j = 0; j < TABLEWIDTH - 1; j++)
		{
			if (!used_variables[j])
			{
				bool validColumn = true;
				bool foundOne = false;
				int onePosition = 0;
				for (i = 0; i < TABLEHEIGHT - 1 && validColumn; i++)
				{
					//onePositions[i] = -1;
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
					//onePositions[j] = onePosition;
					//cout << variables[onePosition] << "/" << onePosition << "/" << j << "/" << i << endl;
				}
			}
		}
		int checkedVariables = 0;
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (variables[i] != -1)
			{
				used_variables[variables[i]] = true;//Переменная отмечается как использованная и в дальнейшем не используется в расчетах
				int usedWeight = 0, usedMoney = 0, usedVolume = 0, itemsBought = 0;		
				//cout << i << "/" << onePositions[i] << endl;
				int a = variables[i];
				itemsBought = Table[a][TABLEWIDTH + TABLEHEIGHT - 2];
				usedWeight = itemsBought * OriginalTable[0][i];
				usedVolume = itemsBought * OriginalTable[1][i];
				usedMoney = itemsBought * OriginalTable[2][i];
								
				cout << "Нужно закупить " << itemsBought << " единиц товара X" << variables[i] + 1 << ", на что уйдет " << usedMoney << " рублей, " << usedWeight << " единиц веса и " << usedVolume << " единиц объема" << endl;
				if (weight - usedWeight > 0 && money - usedMoney > 0 && volume - usedVolume > 0)
				{
					item_type_amount[variables[i]] += itemsBought;					
					cout << "X" << variables[i] + 1 << "* = " << item_type_amount[variables[i]] << endl;
					weight -= usedWeight;
					money -= usedMoney;
					volume -= usedVolume;
					checkedVariables++;
					found_variables++;
					if (usedWeight == 0)
					{
						cout << "Почему-то вес совсем не используется. Решайте дальше сами" << endl;
						weight = 0;
					}
				}
				else
				{
					cout << "X" << variables[i] + 1 << " купить нельзя" << endl;
					weight = 0;
				}
				cout << "Остается " << weight << " ед. нераспределенного веса, " << volume << " ед. нераспределенного объема и " << money << " рублей" << endl;
			}
		}
		/*
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			cout << "|" << item_type_amount[i] << "|" << endl;
		}
		*/
		if (weight > largestWeight)
		{
			for (i = 0; i < TABLEHEIGHT; i++)
			{
				delete(Table[i]);
			}
			delete(Table);
		}
	}
	int itemsToDistribute = 0;
	/*
	int profit[TABLEWIDTH - 1];
	float weightToMoneyRatio[TABLEWIDTH - 1];
	float volumeToMoneyRatio[TABLEWIDTH - 1];
	if (weight > 0 && volume > 0)
	{
		for (int i = 0; i < TABLEWIDTH - 1; i++)
		{
			profit[i] = 0;
			weightToMoneyRatio[i] = 0;
			volumeToMoneyRatio[i] = 0;
			//cout << OriginalTable[0][i] << "/" << weight << "/" << OriginalTable[1][i] << "/" << volume << endl;
			if (OriginalTable[0][i] <= weight && OriginalTable[1][i] <= volume && OriginalTable[2][i] <= money)//Нашли предмет, хотя бы одну единицу которого можно купить и не превысить оставшийся предел веса или объема
			{
				weightToMoneyRatio[i] = OriginalTable[0][i] / OriginalTable[2][i];
				volumeToMoneyRatio[i] = OriginalTable[1][i] / OriginalTable[2][i];
				itemsToDistribute++;
				cout << "Мы можем докупить товар X" << i + 1 << endl;
			}
		}
	}

	if (itemsToDistribute > 0)
	{
		int maxRatioNumber = -1, max = -1;//Постараемся купить товар с самым высоким отношением веса к цене
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (weightToMoneyRatio[i] != 0)
			{
				if (max == -1)
				{
					max = weightToMoneyRatio[i];
					maxRatioNumber = i;
				}				
			}
		}
		int usedWeight = 0, usedMoney = 0, usedVolume = 0, itemsBought = 0;
		int itemWeight = OriginalTable[0][maxRatioNumber], itemCost = OriginalTable[2][maxRatioNumber], ItemVolume = OriginalTable[1][maxRatioNumber];

		do
		{
			usedWeight += itemWeight;
			usedMoney += itemCost;
			usedVolume += ItemVolume;
			//cout << usedWeight << "/" << itemWeight << endl;
			//cout << usedMoney << "/" << itemCost << endl;
			//cout << usedVolume << "/" << ItemVolume << endl;
			itemsBought++;
		} while (usedWeight < weight && usedMoney < money && usedVolume < volume);

		cout << "Докупаем " << itemsBought << " единиц товара X" << maxRatioNumber + 1 << ", на что уйдет " << usedMoney << " рублей, " << usedWeight << " единиц веса и " << usedVolume << " единиц объема" << endl;
		itemsToDistribute = 0;

		item_type_amount[maxRatioNumber] += itemsBought;
	}
	*/
	if (weight == 0 || itemsToDistribute == 0)
	{
		int sumM = 0, sumV = 0, sumS = 0;
		cout << "Имеем план" << endl << "X = (";
		for (i = 0; i < TABLEWIDTH - 1; i++)
		{
			if (item_type_amount[i] > 0)
			{
				cout << item_type_amount[i];
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
			if (item_type_amount[i] > 0)
			{
				cout << item_type_amount[i] << " * " << OriginalTable[0][i];
				sumM += item_type_amount[i] * OriginalTable[0][i];
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
			if (item_type_amount[i] > 0)
			{
				cout << item_type_amount[i] << " * " << OriginalTable[2][i];
				sumS += item_type_amount[i] * OriginalTable[2][i];
			}
			else
			{
				cout << minAmounts[i] << " * " << OriginalTable[2][i];
				sumS += minAmounts[i] * OriginalTable[2][i];
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
		if (sumS <= startMoney)
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
		//cout << "Осталось " << weight << " ед. нераспределенного веса и " << money << " рублей, так как оставшийся вес слишком маленький (меньше самого тяжелого веса - " << largestWeight << ")." << endl;
	}
	
	for (i = 0; i < TABLEHEIGHT; i++)
	{
		delete(OriginalTable[i]);
	}
	delete(OriginalTable);

	return 0;
}