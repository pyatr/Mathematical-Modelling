#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <math.h>
#include <random>
#include <ctime>
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <conio.h>
#include <locale.h>

#define _CRT_SECURE_NO_WARNINGS
#define pff pair<float, float> 

using namespace std;

const int TABLEWIDTH = 3;
const int TABLEHEIGHT = 4;

struct Line
{
public:
	float x1, y1, x2, y2;
};

void EraseGraph()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	RECT rt;
	GetClientRect(hwnd, &rt);
	POINT pt;
	HPEN Pen = CreatePen(PS_SOLID, 10000, RGB(0, 0, 0));
	SelectPen(hdc, Pen);
	MoveToEx(hdc, 0, 0, &pt);
	LineTo(hdc, 0, 0);
}

void DrawPointAt(pff _p, pff offset, float scale, char name[1])
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	RECT rt;
	GetClientRect(hwnd, &rt);
	POINT pt;
	HPEN Pen = CreatePen(PS_SOLID, 8, RGB(250, 250, 250));
	HPEN Pen2 = CreatePen(PS_SOLID, 6, RGB(0, 0, 0));
	SelectPen(hdc, Pen);
	pff p = make_pair(offset.first + _p.first*scale, offset.second - _p.second*scale);
	TextOutA(hdc, p.first - 16, p.second + 8, (LPCSTR)name, 1);
	MoveToEx(hdc, p.first, p.second, &pt);
	LineTo(hdc, p.first, p.second);
	SelectPen(hdc, Pen2);
	MoveToEx(hdc, p.first, p.second, &pt);
	LineTo(hdc, p.first, p.second);
	cout << " " << name << ": " << _p.first << ", " << _p.second << endl;
}

pff LineIntersection(pff A, pff B, pff C, pff D)
{
	float a1 = B.second - A.second;
	float b1 = A.first - B.first;
	float c1 = a1*(A.first) + b1*(A.second);

	float a2 = D.second - C.second;
	float b2 = C.first - D.first;
	float c2 = a2*(C.first) + b2*(C.second);

	float determinant = a1*b2 - a2*b1;

	if (determinant == 0)
	{
		return make_pair(FLT_MAX, FLT_MAX);
	}
	else
	{
		float x = (b2*c1 - b1*c2) / determinant;
		float y = (a1*c2 - a2*c1) / determinant;
		//cout << x << ", " << y << endl;
		return make_pair(x, y);
	}
}

int minnum(int n1, int n2, int n3)
{
	if (n1 < n2 && n1 < n3)
		return n1;
	if (n2 < n1 && n2 < n3)
		return n2;
	if (n3 < n1 && n3 < n2)
		return n3;
	return n1;
}

float LineLength(pff p1, pff p2)
{
	float cat1, cat2;
	cat1 = abs(p1.second);
	cat2 = abs(p2.first);
	float length = sqrtf(cat1*cat2);
	//cout << length;
	return length;
}

void DrawGraphAndSolve(Line *lines, float **Table)
{
	int i;
	float scale = 1.5f;
	float xoffset = 700;
	float yoffset = 700;
	float xlength, ylength;
	xlength = 400 * scale;
	ylength = 400 * scale;
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	RECT rt;
	GetClientRect(hwnd, &rt);
	POINT pt;
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(50, 50, 50));
	HPEN Backgroundpen = CreatePen(PS_SOLID, 2, RGB(50, 50, 50));
	HBRUSH background = CreateSolidBrush(RGB(0, 0, 0));

	SelectBrush(hdc, background);
	SelectPen(hdc, Backgroundpen);

	MoveToEx(hdc, xoffset, yoffset, &pt);
	LineTo(hdc, xoffset + xlength, yoffset);
	LineTo(hdc, xoffset - 30, yoffset);
	LineTo(hdc, xoffset, yoffset);
	LineTo(hdc, xoffset, yoffset - ylength);
	LineTo(hdc, xoffset, yoffset + 30);

	SelectPen(hdc, Pen);
	float linesscale = 10 * scale;
	for (i = 0; i < 3; i++)
	{
		char linenumber[2];
		linenumber[0] = 'l';
		switch (i)
		{
		case 0: linenumber[1] = '1'; break;
		case 1: linenumber[1] = '2'; break;
		case 2: linenumber[1] = '3'; break;
		default: break;
		}
		char coordinatesx[3], coordinatesy[3];
		sprintf(coordinatesx, "%d", (int)lines[i].x1);
		sprintf(coordinatesy, "%d", (int)lines[i].y2);
		TextOutA(hdc, xoffset - 4 - strlen(coordinatesy) * 12, yoffset - lines[i].y2 * linesscale - 8, coordinatesy, 2);
		TextOutA(hdc, xoffset + lines[i].x1 * linesscale, yoffset + 12, coordinatesx, 2);

		TextOutA(hdc, xoffset + 4, yoffset - lines[i].y2 * linesscale - 24, linenumber, 2);
		MoveToEx(hdc, xoffset + lines[i].x1 * linesscale, yoffset - lines[i].y1 * linesscale, &pt);
		LineTo(hdc, xoffset + lines[i].x2 * linesscale, yoffset - lines[i].y2 * linesscale);
	}

	pff pointA, pointB, pointC, pointD;
	pff intersections[3];
	intersections[0] = LineIntersection(make_pair(lines[0].x1, lines[0].y1),
		make_pair(lines[0].x2, lines[0].y2),
		make_pair(lines[1].x1, lines[1].y1),
		make_pair(lines[1].x2, lines[1].y2));
	intersections[1] = LineIntersection(make_pair(lines[0].x1, lines[0].y1),
		make_pair(lines[0].x2, lines[0].y2),
		make_pair(lines[2].x1, lines[2].y1),
		make_pair(lines[2].x2, lines[2].y2));
	intersections[2] = LineIntersection(make_pair(lines[1].x1, lines[1].y1),
		make_pair(lines[1].x2, lines[1].y2),
		make_pair(lines[2].x1, lines[2].y1),
		make_pair(lines[2].x2, lines[2].y2));
	int min = minnum(intersections[0].first, intersections[1].first, intersections[2].first);
	for (i = 0; i < 3; i++)
	{
		if (intersections[i].first == min)
		{
			pointB = intersections[i];
			int n1, n2;
			switch (i)
			{
			case 0: n1 = 1; n2 = 2; break;
			case 1: n1 = 0; n2 = 2; break;
			case 2: n1 = 0; n2 = 1; break;
			default: break;
			}
			if (intersections[n1].first > intersections[n2].first && intersections[n1].second < intersections[n2].second)
			{
				pointC = intersections[n1];
			}
			else
			{
				pointC = intersections[n2];
			}
		}
	}
	
	pointA = make_pair(0, minnum(lines[0].y2, lines[1].y2, lines[2].y2));	
	pointD = make_pair(minnum(lines[0].x1, lines[1].x1, lines[2].x1), 0);
	DrawPointAt(pointA, make_pair(xoffset, yoffset), linesscale, "A");
	DrawPointAt(pointB, make_pair(xoffset, yoffset), linesscale, "B");
	DrawPointAt(pointC, make_pair(xoffset, yoffset), linesscale, "C");
	DrawPointAt(pointD, make_pair(xoffset, yoffset), linesscale, "D");

	float perx = 0, pery = 0;
	perx = Table[TABLEHEIGHT - 1][0] / Table[TABLEHEIGHT - 1][1];
	pery = 1;
	float a = perx;
	perx = pery;
	pery = a;
	cout << " Перпендикуляр x:" << perx << " y:" << pery << endl;
	pery *= -1;

	HPEN Penper = CreatePen(PS_SOLID, 2, RGB(250, 50, 50));
	SelectPen(hdc, Penper);
	MoveToEx(hdc, xoffset - perx * 70, yoffset + pery * linesscale * 10 - pery * 70, &pt);
	LineTo(hdc, xoffset + perx * linesscale * 10 - perx * 70, yoffset - pery * 70);
	/*
	HPEN Penper2 = CreatePen(PS_SOLID, 2, RGB(50, 50, 250));
	SelectPen(hdc, Penper2);
	*/

	pff intersect1b, intersect2b;
	pff intersect1c, intersect2c;
	intersect1b = LineIntersection(pointB, make_pair(0, pointB.second), make_pair(0, pery), make_pair(perx, 0));
	intersect2b = LineIntersection(pointB, make_pair(pointB.first, 0), make_pair(0, pery), make_pair(perx, 0));
	intersect1c = LineIntersection(pointC, make_pair(0, pointC.second), make_pair(0, pery), make_pair(perx, 0));
	intersect2c = LineIntersection(pointC, make_pair(pointC.first, 0), make_pair(0, pery), make_pair(perx, 0));

	/*
	MoveToEx(hdc, xoffset + pointC.first*linesscale, yoffset - pointC.second * linesscale, &pt);
	LineTo(hdc, xoffset - intersect1c.first*linesscale, yoffset - pointC.second * linesscale);
	MoveToEx(hdc, xoffset + pointC.first*linesscale, yoffset - pointC.second * linesscale, &pt);
	LineTo(hdc, xoffset + pointC.first*linesscale, yoffset + intersect2c.second * linesscale);
	MoveToEx(hdc, xoffset + pointB.first*linesscale, yoffset - pointB.second * linesscale, &pt);
	LineTo(hdc, xoffset - intersect1b.first*linesscale, yoffset - pointB.second * linesscale);
	MoveToEx(hdc, xoffset + pointB.first*linesscale, yoffset - pointB.second * linesscale, &pt);
	LineTo(hdc, xoffset + pointB.first*linesscale, yoffset + intersect2b.second * linesscale);
	*/

	float line1b, line2b, line1c, line2c;
	line1b = LineLength(pointB, intersect1b);
	line2b = LineLength(pointB, intersect2b);
	line1c = LineLength(pointC, intersect1c);
	line2c = LineLength(pointC, intersect2c);
	//cout << endl << " line1b " << line1b << endl << " line2b " << line2b << endl << " line1c " << line1c << endl << " line2c " << line2c << endl;

	int solutionline = 0;

	if (line1b + line2b < line1c + line2c/* || true*/)
	{
		cout << " Последняя точка выхода: С" << endl;
		solutionline = 1;
	}
	else
	{
		cout << " Последняя точка выхода: B" << endl;
		solutionline = 2;
	}

	cout << endl << " l1: ";
	float equation1[TABLEWIDTH], equation2[TABLEWIDTH];
	for (i = 0; i < TABLEWIDTH; i++)
	{
		equation1[i] = Table[0][i];
		if (i < TABLEWIDTH - 1)
			cout << equation1[i] << "x" << i + 1;
		if (i < TABLEWIDTH - 2)
			cout << " + ";
		if (i == TABLEWIDTH - 1)
			cout << " = " << equation1[i] << endl;
	}

	cout << " l" << solutionline + 1 << ": ";
	for (i = 0; i < TABLEWIDTH; i++)
	{
		equation2[i] = Table[solutionline][i];
		if (i < TABLEWIDTH - 1)
			cout << equation2[i] << "x" << i + 1;
		if (i < TABLEWIDTH - 2)
			cout << " + ";
		if (i == TABLEWIDTH - 1)
			cout << " = " << equation2[i] << endl;
	}

	float del, del1, del2;
	del = equation1[0] * equation2[1] - equation1[1] * equation2[0];
	del1 = equation1[2] * equation2[1] - equation1[1] * equation2[2];
	del2 = equation1[0] * equation2[2] - equation1[2] * equation2[0];
	cout << " " << equation1[0] << "*" << equation2[1] << " - " << equation1[1] << "*" << equation2[0] << " = " << del << endl;
	cout << " " << equation1[2] << "*" << equation2[1] << " - " << equation1[1] << "*" << equation2[2] << " = " << del1 << endl;
	cout << " " << equation1[0] << "*" << equation2[2] << " - " << equation1[2] << "*" << equation2[0] << " = " << del2 << endl;
	float x1, x2;
	x1 = del1 / del;
	x2 = del2 / del;
	cout << " x1 = " << del1 << "/" << del << " = " << x1 << endl;
	cout << " x2 = " << del2 << "/" << del << " = " << x2 << endl;
	float Z;
	Z = x1 * Table[TABLEHEIGHT - 1][0] + x2 * Table[TABLEHEIGHT - 1][1];
	cout << " Z = " << x1 << "*" << Table[TABLEHEIGHT - 1][0] << " + " << x2 << "*" << Table[TABLEHEIGHT - 1][1] << " = " << Z;
}

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

float **ConvertToTable(string *Rows, string *B, string *C)
{
	int i, j;
	float **NewTable = 0;
	NewTable = new float*[TABLEHEIGHT];

	for (i = 0; i < TABLEHEIGHT; i++)
	{
		NewTable[i] = new float[TABLEWIDTH];
		for (j = 0; j < TABLEWIDTH; j++)
		{
			NewTable[i][j] = 0;
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
		NewTable[i][TABLEWIDTH + - 1] = stof(Bs[i]);
		//cout << NewTable[i][TABLEWIDTH - 1] << " ";
	}
	//cout << endl;

	vector<string> Cs = Split(*C);
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		NewTable[TABLEHEIGHT - 1][i] = stof(Cs[i]);
		//cout << NewTable[TABLEHEIGHT - 1][i] << " ";
	}
	//cout << NewTable[TABLEHEIGHT - 1][TABLEWIDTH - 1];
	//cout << endl;
	return NewTable;
}

string SetPrecision(string s)
{
	int precision = 0;
	int l = s.length();
	string news = s;
	for (int i = 0; i < l; i++)
	{
		if (s[i] == ',')
		{
			if (precision == 0)
				news = s.substr(0, i);
			else
				news = s.substr(0, i + precision + 1);
		}
	}
	return news;
}

int main()
{
	int i, j;
	int Iteration = 0, Iterations = 0;
	string Rows[TABLEHEIGHT - 1];
	/*string B = "42, 72, 60";
	string C = "15, 20";
	Rows[0] = "3, 2";
	Rows[1] = "6, 2";
	Rows[2] = "3, 4";*/
	string B = "32, 36, 21";
	string C = "10, 25";
	Rows[0] = "8, 4";
	Rows[1] = "6, 9";
	Rows[2] = "1, 3";
	/*string B = "24, 24, 21";
	string C = "15, 18";
	Rows[0] = "6, 3";
	Rows[1] = "4, 6";
	Rows[2] = "1, 3";*/
	setlocale(LC_ALL, "RUS");
	float **Table = ConvertToTable(Rows, &B, &C);
	cout << endl;
	for (i = 0; i < TABLEHEIGHT - 1; i++)
	{
		string uneq = " ";
		for (j = 0; j < TABLEWIDTH - 1; j++)
		{
			uneq += SetPrecision(to_string(Table[i][j]));
			uneq += "*x" + to_string(j + 1);
			if (j < TABLEWIDTH - 2)
				uneq += " + ";
			else
				uneq += " <= ";
		}
		uneq += SetPrecision(to_string(Table[i][j]));
		cout << uneq << endl;
	}
	cout << endl;
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		cout << " x" << to_string(i) << " => 0" << endl;
	}
	cout << endl << " Z = ";
	for (i = 0; i < TABLEWIDTH - 1; i++)
	{
		cout << SetPrecision(to_string(Table[TABLEHEIGHT - 1][i])) << "x" << to_string(i + 1);
		if (i < TABLEWIDTH - 2)
			cout << " + ";
		else
			cout << " --> max";
	}
	cout << endl << endl;

	Line *lines = (Line*)malloc(sizeof(Line)*(TABLEHEIGHT - 1));
	for (int i = 0; i < TABLEHEIGHT - 1; i++)
	{
		Line newline;
		newline.x1 = Table[i][2] / Table[i][0];
		newline.y1 = 0;
		newline.x2 = 0;
		newline.y2 = Table[i][2] / Table[i][1];
		lines[i] = newline;
		cout << " (" << lines[i].x1 << ";" << lines[i].y1 << ") (" << lines[i].x2 << ";" << lines[i].y2 << ") " << endl;	
	}

	DrawGraphAndSolve(lines, Table);

	delete(lines);
	for (i = 0; i < TABLEHEIGHT; i++)
	{
		delete(Table[i]);
	}
	delete(Table);
	cout << endl;
	return 0;
}