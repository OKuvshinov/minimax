// minimax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>

#define PI 3.14159265358979323
#define PRINT_TABLE 0

using namespace std;

int startTime;

typedef struct
{
	double value;
	double u;
	double v;
} pointInstance;

pointInstance minimax, maximin;
double a, b, c, d;
int N, K;
double delta, Delta;

double **matrix;
/*Нужно динамически выделить память*/

double f(double u, double v);

void find_minimax(void);
void find_maximin(void);

void countMatrix(void);

int main()
{
	startTime = clock();
	cout << fixed;
	cout.precision(3);

	a = sqrt(PI / (double)3);
	b = sqrt((double)2 * PI / (double)3);
	N = 1000;
	delta = (b - a) / double(N);

	cout << "a = " << a << " b = " << b << " delta = " << delta << endl;
	
	c = sqrt(PI / (double)3);
	d = sqrt((double)2*PI/(double)3);
	K = 1000;
	Delta = (d - c) / double(K);

	cout << "c = " << c << " d = " << d << " Delta = " << Delta << endl << endl;

	find_minimax();
	find_maximin();

	cout << endl;
	cout << "minimax: " << minimax.value << ", u = " << minimax.u << ", v = " << minimax.v << endl;
	cout << "maximin: " << maximin.value << ", u = " << maximin.u << ", v = " << maximin.v << endl;
	cout << "difference: " << minimax.value - maximin.value << endl << endl;

	cout << clock() - startTime << " ms" << endl;
	system("pause");
}

double f(double u, double v)
{
	return sin(u*v);
}

void find_minimax(void)
{
	pointInstance localMax;
	double localResult = 0;
	double ui = a, vj = c;
	int allMaxCounter = 0;

	for (ui = a; ui <= b; ui += delta)
	{
		vj = c;
		localMax.value = f(ui, vj);
		localMax.u = ui;
		localMax.v = vj;

		for (vj = c; vj <= d; vj += Delta)
		{
			localResult = f(ui, vj);
			
			#if PRINT_TABLE
			cout << localResult << " ";
			#endif

			if (localResult > localMax.value)
			{
				localMax.value = localResult;
				localMax.u = ui;
				localMax.v = vj;
			}
		}

		#if PRINT_TABLE
		cout << endl;
		#endif

		if (((allMaxCounter > 0) && (localMax.value < minimax.value))
		 || (allMaxCounter == 0))
		{
			minimax.value = localMax.value;
			minimax.u = localMax.u;
			minimax.v = localMax.v;
		}

		allMaxCounter++;
	}
}

void find_maximin(void)
{
	pointInstance localMin;
	double localResult = 0;
	double ui = a, vj = c;
	int allMinCounter = 0;

	for (vj = c; vj <= d; vj += Delta)
	{
		ui = a;
		localMin.value = f(ui, vj);
		localMin.u = ui;
		localMin.v = vj;

		for (ui = a; ui <= b; ui += delta)
		{
			localResult = f(ui, vj);
			if (localResult < localMin.value)
			{
				localMin.value = localResult;
				localMin.u = ui;
				localMin.v = vj;
			}
		}

		if (((allMinCounter > 0) && (localMin.value > maximin.value))
			|| (allMinCounter == 0))
		{
			maximin.value = localMin.value;
			maximin.u = localMin.u;
			maximin.v = localMin.v;
		}

		allMinCounter++;
	}
}

void countMatrix(void)
{
	double ui = a, vj = c;
	int i = 0, j = 0;

	for (ui = a; ui <= b; ui += delta)
	{
		j = 0;
		for (vj = c; vj <= d; vj += Delta)
		{
			matrix[i][j] = f(ui, vj);
			cout << matrix[i][j] << " ";
			j++;
		}
		cout << endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
