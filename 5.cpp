#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

const int ROWWIDTH = 8;

void BuildLinearModel(double *rowX, double *rowY)
{
	int i, j;
	double sumX = 0, sumY = 0, sumXY = 0, sumXpow2 = 0;
	double a, b;
	cout << "Ћинейна€ модель:	 E(x^2)*a + E(x)*b = E(x*y)" << endl;
	cout << "			 E(x)*a + E()*b = E(y)" << endl;
	cout << "E(x)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumX += rowX[i];
		cout << rowX[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumX << endl;
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
	cout << "E(x*y)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumXY += rowX[i] * rowY[i];
		cout << rowX[i] << "*" << rowY[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumXY << endl;
	cout << "E(x^2)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumXpow2 += rowX[i] * rowX[i];
		cout << rowX[i] << "^2";
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumXpow2 << endl << endl;
	cout << sumXpow2 << "*a + " << sumX << "*b = " << sumXY << endl;
	cout << sumX << "*a + " << ROWWIDTH << "*b = " << sumY << endl;
	double del, del1, del2;
	del = sumXpow2*ROWWIDTH - sumX * sumX;
	del1 = sumXY*ROWWIDTH - sumY * sumX;
	del2 = sumXpow2*sumY - sumX*sumXY;
	cout << "delta = " << sumXpow2 << "*" << ROWWIDTH << " - " << sumX << "*" << sumX << " = " << del << endl;
	cout << "delta1 = " << sumXY << "*" << ROWWIDTH << " - " << sumY << "*" << sumX << " = " << del1 << endl;
	cout << "delta2 = " << sumXpow2 << "*" << sumY << " - " << sumX << "*" << sumXY << " = " << del2 << endl;
	a = del1 / del;
	b = del2 / del;
	cout << "a = " << del1 << "/" << del << " = " << a << endl;
	cout << "b = " << del2 << "/" << del << " = " << b << endl;
	char porm = '+';
	if (b < 0)
		porm = '-';
	cout << "Ћинейное уравнение yt = " << a << "*x " << porm << " " << abs(b) << endl;
	double yt[ROWWIDTH];
	cout << "x |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowX[i] << "		|";
	}
	cout << endl << "y |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowY[i] << "		|";
	}
	cout << endl << "yt|";
	for (i = 0; i < ROWWIDTH; i++)
	{
		yt[i] = rowX[i] * a + b;
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
	int k = 2;
	Ssys2 = Q1 / (ROWWIDTH - 1);
	cout << "Ssys^2 = " << Q1 << "/(" << ROWWIDTH << " - 1) = " << Ssys2 << endl;
	Smod2 = Q2 / (k - 1);
	cout << "Smod^2 = " << Q2 << "/(" << k << " - 1) = " << Smod2 << endl;
	Srest2 = Q3 / (ROWWIDTH - k);
	cout << "Srest^2 = " << Q3 << "/(" << ROWWIDTH << " - " << k << ") = " << Srest2 << endl;
	Fcalc = Smod2 / Srest2;
	cout << "Fcalc = " << Smod2 << "/" << Srest2 << " = " << Fcalc << endl;
}

void BuildQuadraticModel(double *rowX, double *rowY)
{
	int i, j;
	double sumX = 0, sumY = 0, sumXY = 0, sumXpow2 = 0;
	double sumXpow4 = 0, sumXpow3 = 0, sumXpow2Y = 0;
	cout << " вадратическа€ модель:	 E(x^4)*a + E(x^3)*b + E(x^2)*c = E(x^2*y)" << endl;
	cout << "			 E(x^3)*a + E(x^2)*b + E(x)*c = E(x*y)" << endl;
	cout << "			 E(x^2)*a + E(x)*b + E()*c*n = E(y)" << endl;
	cout << "E(x)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumX += rowX[i];
		cout << rowX[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumX << endl;
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
	cout << "E(x*y)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumXY += rowX[i] * rowY[i];
		cout << rowX[i] << "*" << rowY[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumXY << endl;
	cout << "E(x^2)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumXpow2 += rowX[i] * rowX[i];
		cout << rowX[i] << "^2";
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumXpow2 << endl;
	cout << "E(x^2*y)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumXpow2Y += rowX[i] * rowX[i] * rowY[i];
		cout << rowX[i] << "^2*" << rowY[i];
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumXpow2Y << endl;
	cout << "E(x^3)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumXpow3 += rowX[i] * rowX[i] * rowX[i];
		cout << rowX[i] << "^3";
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumXpow3 << endl;
	cout << "E(x^4)" << endl;
	for (i = 0; i < ROWWIDTH; i++)
	{
		sumXpow4 += rowX[i] * rowX[i] * rowX[i] * rowX[i];
		cout << rowX[i] << "^4";
		if (i < ROWWIDTH - 1)
			cout << " + ";
		else
			cout << " = ";
	}
	cout << sumXpow4 << endl << endl;

	cout << sumXpow4 << "*a + " << sumXpow3 << "*b + " << sumXpow2 << "*c = " << sumXpow2Y << endl;
	cout << sumXpow3 << "*a + " << sumXpow2 << "*b + " << sumX << "*c = " << sumXY << endl;
	cout << sumXpow2 << "*a + " << sumX << "*b + " << ROWWIDTH << "*c = " << sumY << endl;

	double a[3][3], e[3];
	a[0][0] = sumXpow4;
	a[0][1] = sumXpow3;
	a[0][2] = sumXpow2;
	a[1][0] = sumXpow3;
	a[1][1] = sumXpow2;
	a[1][2] = sumX;
	a[2][0] = sumXpow2;
	a[2][1] = sumX;
	a[2][2] = ROWWIDTH;
	e[0] = sumXpow2Y;
	e[1] = sumXY;
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
	cout << " вадратное уравнение yt = " << av << "*x^2 " << porm << " " << abs(bv) << "*x ";
	porm = '+';
	if (cv < 0)
		porm = '-';
	cout << porm << " " << abs(cv) << endl;
	double yt[ROWWIDTH];
	cout << "x |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowX[i] << "		|";
	}
	cout << endl << "y |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowY[i] << "		|";
	}
	cout << endl << "yt|";
	for (i = 0; i < ROWWIDTH; i++)
	{
		yt[i] = pow(rowX[i], 2) * av + rowX[i] * bv + cv;
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
	int k = 2;
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
	double rowX[ROWWIDTH], rowY[ROWWIDTH];
	for (i = 0; i < ROWWIDTH; i++)
	{
		rowX[i] = i + 1;
	}	
	
	rowY[0] = 6;
	rowY[1] = 21;
	rowY[2] = 34;
	rowY[3] = 54;
	rowY[4] = 89;
	rowY[5] = 111;
	rowY[6] = 179;
	rowY[7] = 280;
	
	cout << "x |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowX[i] << "	|";
	}
	cout << endl << "y |";
	for (i = 0; i < ROWWIDTH; i++)
	{
		cout << rowY[i] << "	|";
	}
	cout << endl << endl;
	BuildLinearModel(rowX, rowY);
	cout << "[-----------------------------------------------------------------------------------------------------]" << endl;
	cout << "[-----------------------------------------------------------------------------------------------------]" << endl;
	BuildQuadraticModel(rowX, rowY);
	return 0;
}