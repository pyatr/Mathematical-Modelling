#include "pch.h"
#include <iostream>
#include <locale.h>
#include <vector>

using namespace std;

const int ITEMTYPES = 8;
const int WEIGHTLIMIT = 30;//25;

class Variant
{
public:
	int mass = 0, profit = 0;
	bool usedItems[ITEMTYPES];

	Variant()
	{
		for (int i = 0; i < ITEMTYPES; i++)
		{
			usedItems[i] = false;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "RUS");
	int i;
	int mass[ITEMTYPES] = { 2,3,4,5,6,7,8,9 };//{ 1,2,3,4,5,6,7,8 };
	int value[ITEMTYPES] = { 320,570,680,800,900,980,1040,1080 }; //{ 120,150,180,220,320,300,350,360 };
	int ratio[ITEMTYPES];
	bool chosenItems[ITEMTYPES];
	int chosenItemAmount = 0;
	for (i = 0; i < ITEMTYPES; i++)
	{
		ratio[i] = value[i] / mass[i];//Выявляем удельную стоимость
		chosenItems[i] = false;
	}

	for (i = 0; i < 4; i++)
	{
		for (int j = 0; j < ITEMTYPES + 1; j++)
		{
			cout << "|";
			switch (i)
			{
			case 0:
				if (j == 0)
					cout << "	";
				else
					cout << "T" << j;
				break;
			case 1:
				if (j == 0)
					cout << "Масса  ";
				else
					cout << mass[j - 1];
				break;
			case 2:
				if (j == 0)
					cout << "Прибыль";
				else
					cout << value[j - 1];
				break;
			case 3:
				if (j == 0)
					cout << "Уд. цен.";
				else
					cout << ratio[j - 1];
				break;
			default: break;
			}
			cout << "	";
		}
		cout << "|" << endl;
	}
	int usedWeight = 0, profit = 0;
	while (usedWeight <= WEIGHTLIMIT)
	{
		int mostExpensiveItemNumber = -1;
		for (i = 0; i < ITEMTYPES; i++)
		{
			if (!chosenItems[i])
			{
				if (mostExpensiveItemNumber == -1)
				{
					mostExpensiveItemNumber = i;
				}
				if (ratio[mostExpensiveItemNumber] == ratio[i])
				{
					if (value[mostExpensiveItemNumber] < value[i])
					{
						//cout << "T" << mostExpensiveItemNumber + 1 << "/" << value[mostExpensiveItemNumber] << " < T" << i + 1 << "/" << value[i]<<endl;
						mostExpensiveItemNumber = i;
					}
				}
				if (ratio[mostExpensiveItemNumber] < ratio[i])
				{
					mostExpensiveItemNumber = i;
				}
			}
		}
		chosenItems[mostExpensiveItemNumber] = true;
		chosenItemAmount++;
		usedWeight += mass[mostExpensiveItemNumber];
		profit += value[mostExpensiveItemNumber];
		int printedValues = 0;
		cout << "Ранец = {";
		for (i = 0; i < ITEMTYPES; i++)
		{
			if (chosenItems[i])
			{
				cout << "T" << i + 1;
				printedValues++;
				if (printedValues < chosenItemAmount)
				{
					cout << ", ";
				}
			}
		}
		cout << "}" << endl;
		printedValues = 0;
		cout << "Масса = ";
		for (i = 0; i < ITEMTYPES; i++)
		{
			if (chosenItems[i])
			{
				cout << mass[i];
				printedValues++;
				if (printedValues < chosenItemAmount)
				{
					cout << " + ";
				}
			}
		}
		cout << " = " << usedWeight << endl;
		printedValues = 0;
		cout << "Прибыль = ";
		for (i = 0; i < ITEMTYPES; i++)
		{
			if (chosenItems[i])
			{
				cout << value[i];
				printedValues++;
				if (printedValues < chosenItemAmount)
				{
					cout << " + ";
				}
			}
		}
		cout << " = " << profit << endl;
	}
	if (usedWeight > WEIGHTLIMIT)
	{
		int overload = usedWeight - WEIGHTLIMIT;
		cout << endl << "Перегруз = " << overload << endl << endl;
		bool possibleItemsToDrop[ITEMTYPES];
		int variantCount = 0;
		for (i = 0; i < ITEMTYPES; i++)
		{
			if (chosenItems[i])
			{
				if (mass[i] >= overload)
				{
					possibleItemsToDrop[i] = true;
					variantCount++;
				}
				else
					possibleItemsToDrop[i] = false;
			}
		}
		vector<Variant> variants;
		variants.reserve(variantCount);

		for (i = 0; i < variantCount; i++)
		{
			Variant newVariant = Variant();
			int dropNumber = -1;
			for (int j = 0; j < ITEMTYPES; j++)
			{
				if (chosenItems[j])
				{
					if (possibleItemsToDrop[j] == true)//Убираем товар, который не убирали ранее
					{
						if (dropNumber == -1)
						{
							possibleItemsToDrop[j] = false;
							dropNumber = j;
						}
					}
					if (dropNumber != j)
					{
						newVariant.mass += mass[j];
						newVariant.profit += value[j];
						newVariant.usedItems[j] = true;
					}
				}
			}
			variants.insert(variants.end(), newVariant);
		}

		for (i = 0; i < variantCount; i++)//Вывод возможных вариантов
		{
			cout << "Вариант " << i + 1 << endl;
			for (int j = 0; j < ITEMTYPES; j++)
			{
				if (variants[i].usedItems[j])
				{
					cout << "T" << j + 1;
				}
				if (variants[i].usedItems[j + 1] && j < chosenItemAmount - 1)
				{
					cout << " + ";
				}
			}
			cout << " = " << variants[i].mass << endl;
			for (int j = 0; j < ITEMTYPES; j++)
			{
				if (variants[i].usedItems[j])
				{
					cout << value[j];
				}
				if (variants[i].usedItems[j + 1] && j < chosenItemAmount - 1)
				{
					cout << " + ";
				}
			}
			cout << " = " << variants[i].profit << endl;
		}
		//Начинаем искать исправления вариантов, количество вариантов может увеличиться
		cout << endl;
		vector<Variant> totalVariants;
		for (i = 0; i < variantCount; i++)
		{
			int diff = WEIGHTLIMIT - variants[i].mass;
			if (diff > 0)
			{
				bool possibleReplacements[ITEMTYPES];
				int replacementsLeft = 0;
				for (int j = 0; j < ITEMTYPES; j++)
				{
					possibleReplacements[j] = !variants[i].usedItems[j];
					if (possibleReplacements[j])
						replacementsLeft++;
				}
				Variant originalVariant = variants[i];
			anotherVariant:
				variants[i] = originalVariant;
				cout << "Вариант " << i + 1 << endl;
				for (int j = 0; j < ITEMTYPES; j++)
				{
					if (!variants[i].usedItems[j] && possibleReplacements[j])//Ищем товар, который можно заменить				
					{
						//cout << "Товар №" << j + 1 << " в варианте " << i + 1 << " не используемся, попробуем им что-нибудь заменить" << endl;
						for (int k = 0; k < ITEMTYPES; k++)
						{
							if (chosenItems[k])
							{
								if (k != j)
								{
									if (value[k] < value[j])
									{
										//cout << "Товар №" << k + 1 << " дешевле товара №" << j + 1 << "(" << value[k] << "<" << value[j] << ")" << endl;
										if (mass[j] - mass[k] <= diff)
										{
											cout << "Заменяем товаром №" << j + 1 << " товар №" << k + 1 << endl;
											variants[i].mass += mass[j];
											variants[i].profit += value[j];
											variants[i].usedItems[j] = true;
											variants[i].mass -= mass[k];
											variants[i].profit -= value[k];
											variants[i].usedItems[k] = false;
											possibleReplacements[j] = false;
											replacementsLeft--;
											j = ITEMTYPES;
										}
									}
									else
									{
										//cout << "Товар №" << k + 1 << " дороже товара №" << j + 1 << "(" << value[k] << ">" << value[j] << ")" << endl;
									}
								}
							}
						}
					}
				}
				for (int j = 0; j < ITEMTYPES; j++)
				{
					if (variants[i].usedItems[j])
					{
						cout << "T" << j + 1 << " ";
					}
				}
				cout << "= " << variants[i].mass << endl;
				for (int j = 0; j < ITEMTYPES; j++)
				{
					if (variants[i].usedItems[j])
					{
						cout << value[j] << " ";
					}
				}
				cout << "= " << variants[i].profit << endl;

				totalVariants.push_back(variants[i]);
				if (replacementsLeft)
				{
					//cout << "Рассмотрены не все варианты исправления варианта " << i + 1 << ", продолжаем рассматривать" << endl;
					goto anotherVariant;
				}
			}
			totalVariants.push_back(variants[i]);//Если вариант уже оптимален, т.е. его вес равен предельному, его все равно нужно занести в список всех возможных варинатов
		}

		Variant maxVariant = totalVariants[0];
		for (i = 0; i < totalVariants.size(); i++)
		{			
			if (maxVariant.profit < totalVariants[i].profit)
				maxVariant.profit = totalVariants[i].profit;
		}
		cout << endl;
		cout << "Самый оптимальный план имеет вес " << maxVariant.mass << " и товаров на сумму " << maxVariant.profit << endl;
		for (int j = 0; j < ITEMTYPES; j++)
		{
			if (maxVariant.usedItems[j])
			{
				cout << "T" << j + 1 << " ";
				if (j < ITEMTYPES - 2||maxVariant.usedItems[j + 1])				
						cout << "+ ";				
			}
		}
		cout << endl;
		for (int j = 0; j < ITEMTYPES; j++)
		{
			if (maxVariant.usedItems[j])
			{
				cout << value[j] << " ";
				if (j < ITEMTYPES - 2 || maxVariant.usedItems[j + 1])				
					cout << "+ ";				
			}
		}
	}
	else
	{
		cout << "Перегруза нет" << endl;
	}
	return 0;
}