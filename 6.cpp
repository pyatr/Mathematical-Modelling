#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

const int ROWWIDTH = 8;

void BuildModel(double *rowX1, double *rowX2, double *rowY)
{
	int i, j;
	double sumX1 = 0, sumX2 = 0, multX1X2 = 0, sumY = 0, sumX1Y = 0, sumX2Y = 0, sumX1pow2 = 0, sumX2pow2 = 0;

	cout << "a*E(x1^2) + b*E(x1*x2) + c*E(x1) = E(x1*y)" << endl;
	cout << "a*E(x1*x2) + b*E(x^2) + c*E(x2) = E(x2*y)" << endl;
	cout << "a*E(x1) + b*E(x) + c*E()*n = E(y)" << endl;
	cout << "E(x1)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumX1 += rowX1[i];
		cout << rowX1[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumX1 << endl;
	cout << "E(x2)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumX2 += rowX2[i];
		cout << rowX2[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumX2 << endl;
	cout << "E(y)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumY += rowY[i];
		cout << rowY[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumY << endl;
	cout << "E(x1*y)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumX1Y += rowX1[i] * rowY[i];
		cout << rowX1[i] << "*" << rowY[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumX1Y << endl;
	cout << "E(x2*y)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumX2Y += rowX2[i] * rowY[i];
		cout << rowX2[i] << "*" << rowY[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumX2Y << endl;
	cout << "E(x1^2)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumX1pow2 += pow(rowX1[i], 2);
		cout << pow(rowX1[i], 2);
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumX1pow2 << endl;
	cout << "E(x2^2)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumX2pow2 += pow(rowX2[i], 2);
		cout << pow(rowX2[i], 2);
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumX2pow2 << endl;
	cout << "E(x1*x2)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		multX1X2 += rowX1[i] * rowX2[i];
		cout << rowX1[i] << " * " << rowX2[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumX2pow2 << endl;

	cout << sumX1pow2 << "*a + " << multX1X2 << "*b + " << sumX1 << "*c = " << sumX1Y << endl;
	cout << multX1X2 << "*a + " << sumX2pow2 << "*b + " << sumX2 << "*c = " << sumX2Y << endl;
	cout << sumX1 << "*a + " << sumX2 << "*b + " << ROWWIDTH << "*c = " << sumY << endl;

	double a[3][3], e[3];
	a[0][0] = sumX1pow2;
	a[0][1] = multX1X2;
	a[0][2] = sumX1;
	a[1][0] = multX1X2;
	a[1][1] = sumX2pow2;
	a[1][2] = sumX2;
	a[2][0] = sumX1;
	a[2][1] = sumX2;
	a[2][2] = ROWWIDTH;
	e[0] = sumX1Y;
	e[1] = sumX2Y;
	e[2] = sumY;

	int del[4];

	for (int k = 0; k < 4; k++)
	{
		float a2[3][3];
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				a2[i][j] = a[i][j];
			}
		}

		if (k > 0)
		{
			for (i = 0; i < 3; i++)
			{
				a2[i][k - 1] = e[i];
			}
		}
		int p1, p2, p3, p4, p5, p6;
		p1 = a2[0][0] * a2[1][1] * a2[2][2];
		p2 = a2[1][0] * a2[2][1] * a2[0][2];
		p3 = a2[2][0] * a2[0][1] * a2[1][2];
		p4 = a2[0][2] * a2[1][1] * a2[2][0];
		p5 = a2[0][0] * a2[2][1] * a2[1][2];
		p6 = a2[1][0] * a2[0][1] * a2[2][2];
		del[k] = p1 + p2 + p3 - p4 - p5 - p6;
		char num = ' ';
		if (k > 0)
			num = k + 48;
		cout << "del" << num << " = " << p1 << " + " << p2 << " + " << p3 << " - " << p4 << " - " << p5 << " - " << p6 << " = " << del[k] << endl;
	}

	double av, bv, cv;
	av = (double)del[1] / del[0];
	bv = (double)del[2] / del[0];
	cv = (double)del[3] / del[0];
	cout << "a = " << del[1] << "/" << del[0] << " = " << av << endl;
	cout << "b = " << del[2] << "/" << del[0] << " = " << bv << endl;
	cout << "c = " << del[3] << "/" << del[0] << " = " << cv << endl;
	char porm = '+';
	if (bv < 0)
		porm = '-';
	cout << "yt = " << av << "*x1 " << porm << " " << abs(bv) << "*x2 ";
	porm = '+';
	if (cv < 0)
		porm = '-';
	cout << porm << " " << abs(cv) << endl;

	double yt[ROWWIDTH];
	cout << "x1 |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowX1[i] << "		|";
	}
	cout << "x2 |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowX2[i] << "		|";
	}
	cout << endl << "y |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowY[i] << "		|";
	}
	cout << endl << "yt|";
	for (i = 0; i < ROWWIDTH; i++)
	{
		yt[i] = rowX1[i] * av + rowX2[i] * bv + cv;
		cout << yt[i] << " 	|";
	}
	cout << endl << endl;
	double ys = sumY / ROWWIDTH;
	cout << "_" << endl;
	cout << "y = " << ys << endl;
	double Q1 = 0, Q2 = 0, Q3 = 0;
	cout << "Q1 = ";
	for (i = 0; i < ROWWIDTH; i++)
	{
		Q1 += pow((rowY[i] - ys), 2);
		cout << "(" << rowY[i] << "-" << ys << ")^2";
		if (i < ROWWIDTH - 1)
			cout << "+";
		else
			cout << " = ";
	}
	cout << Q1 << endl;
	cout << "Q2 = ";
	for (i = 0; i < ROWWIDTH; i++)
	{
		Q2 += pow(yt[i] - ys, 2);
		cout << "(" << yt[i] << "-" << ys << ")^2";
		if (i < ROWWIDTH - 1)
			cout << "+";
		else
			cout << " = ";
	}
	cout << Q2 << endl;
	cout << "Q3 = ";
	for (i = 0; i < ROWWIDTH; i++)
	{
		Q3 += pow(yt[i] - rowY[i], 2);
		cout << "(" << yt[i] << "-" << rowY[i] << ")^2";
		if (i < ROWWIDTH - 1)
			cout << "+";
		else
			cout << " = ";
	}
	cout << Q3 << endl;
	double D, I, Ssys2, Smod2, Srest2, Fcalc;
	D = 1 - Q3 / Q1;
	cout << "D = " << D << endl;
	I = sqrt(D);
	cout << "I = " << I << endl;
	if (I > 0.9)
		cout << "I > 0.9: ќценка положительна€" << endl;
	else
	{
		if (I > 0.7)
			cout << "I > 0.7: ќценка хороша€" << endl;
		else
		{
			if (I > 0.3)
				cout << "I > 0.3: ќценка посредственна€" << endl;
		}
	}
	int k = 3;
	Ssys2 = Q1 / (ROWWIDTH - 1);
	cout << "Ssys^2 = " << Q1 << "/(" << ROWWIDTH << " - 1) = " << Ssys2 << endl;
	Smod2 = Q2 / (k - 1);
	cout << "Smod^2 = " << Q2 << "/(" << k << " - 1) = " << Smod2 << endl;
	Srest2 = Q3 / (ROWWIDTH - k);
	cout << "Srest^2 = " << Q3 << "/(" << ROWWIDTH << " - " << k << ") = " << Srest2 << endl;
	Fcalc = Smod2 / Srest2;
	cout << "Fcalc = " << Smod2 << "/" << Srest2 << " = " << Fcalc << endl;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int i, j;
	double rowX1[ROWWIDTH], rowX2[ROWWIDTH], rowY[ROWWIDTH];
	for (i = 0; i < ROWWIDTH/2; i++)
	{
		rowX1[i] = i + 1;
		rowX1[i+4] = i + 1;
	}

	rowX2[0] = 2;
	rowX2[1] = 2;
	rowX2[2] = 2;
	rowX2[3] = 2;
	rowX2[4] = 3;
	rowX2[5] = 3;
	rowX2[6] = 3;
	rowX2[7] = 3;

	rowY[0] = 9;
	rowY[1] = 12;
	rowY[2] = 15;
	rowY[3] = 17;
	rowY[4] = 32;
	rowY[5] = 36;
	rowY[6] = 39;
	rowY[7] = 43;	

	cout << "x1 |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowX1[i] << "	|";
	}
	cout << endl << "x2 |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowX2[i] << "	|";
	}
	cout << endl << "y |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowY[i] << "	|";
	}
	cout << endl << endl;
	BuildModel(rowX1, rowX2, rowY);
	return 0;
}