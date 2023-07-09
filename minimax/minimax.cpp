// minimax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>

#include <fstream>

#define PI 3.14159265358979323
#define PRINT_TABLE 0
#define WITH_MATRIX 0

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

pointInstance **matrix;
/*Нужно динамически выделить память*/

double f(double u, double v);

void find_minimax(void);
void find_maximin(void);

void countMatrix(void);

ofstream wrMinimax;
ofstream wrMaximin;

int main()
{
	startTime = clock();
	cout << fixed;
	cout.precision(3);

	a = sqrt((double)1 * (PI / (double)6));
	b = sqrt((double)5 * (PI / (double)6));
	N = 100;
	delta = (b - a) / double(N);
	cout << "a = " << a << " b = " << b << " delta = " << delta << endl;
	
	c = a;
	d = b;
	K = 100;
	Delta = (d - c) / double(K);
	cout << "c = " << c << " d = " << d << " Delta = " << Delta << endl << endl;

#if WITH_MATRIX
	matrix = new pointInstance*[N + 1];
	for (int i = 0; i <= N; i++)
		matrix[i] = new pointInstance[K + 1];

	countMatrix();
#endif

	wrMinimax.open("minimax.txt");
	wrMaximin.open("maximin.txt");
	if ((wrMinimax.is_open()) && (wrMaximin.is_open()))
	{
		do
		{
			find_minimax();
			find_maximin();
			a -= delta;
		} while (a>-1*sqrt((double)5 * (PI / (double)6)));

		wrMinimax.close();
		wrMaximin.close();

		cout << endl;
		cout << "minimax: " << minimax.value << ", u = " << minimax.u << ", v = " << minimax.v << endl;
		cout << "maximin: " << maximin.value << ", u = " << maximin.u << ", v = " << maximin.v << endl;
		cout << "difference: " << minimax.value - maximin.value << endl << endl;

		cout << clock() - startTime << " ms" << endl;
	}
	system("pause");
}

double f(double u, double v)
{
	return sin(u*v);
}

void find_minimax(void)
{
#if WITH_MATRIX
	pointInstance localMax;
	double localResult = 0;
	int i = 0, j = 0;
	int allMaxCounter = 0;	

	for (i = 0; i < N; i++)
	{
		j = 0;
		localMax.value = matrix[i][j].value;
		localMax.u = matrix[i][j].u;
		localMax.v = matrix[i][j].v;
		for (j = 0; j < K; j++)
		{
			if (matrix[i][j].value > localMax.value)
			{
				localMax.value = matrix[i][j].value;
				localMax.u = matrix[i][j].u;
				localMax.v = matrix[i][j].v;
			}
		}

		if (((allMaxCounter > 0) && (localMax.value < minimax.value))
		 || (allMaxCounter == 0))
		{
			minimax.value = localMax.value;
			minimax.u = localMax.u;
			minimax.v = localMax.v;
		}

		allMaxCounter++;
	}

	wrMinimax << a << " " << minimax.value << endl;
#else
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

	wrMinimax << a << " " << minimax.value << endl;
#endif
}

void find_maximin(void)
{
#if WITH_MATRIX
	pointInstance localMin;
	double localResult = 0;
	int i = 0, j = 0;
	int allMinCounter = 0;

	for (i = 0; i <= N; i++)
	{
		j = 0;
		localMin.value = matrix[i][j].value;
		localMin.u = matrix[i][j].u;
		localMin.v = matrix[i][j].v;
		for (j = 0; j <= K; j++)
		{
			if (matrix[i][j].value < localMin.value)
			{
				localMin.value = matrix[i][j].value;
				localMin.u = matrix[i][j].u;
				localMin.v = matrix[i][j].v;
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

	wrMaximin << a << " " << maximin.value << endl;
#else
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

	wrMaximin << a << " " << maximin.value << endl;
#endif
}

void countMatrix(void)
{
	double ui = a, vj = c;
	int i = 0, j = 0;

	for (ui = a; ui <= b+delta/2; ui += delta)
	{
		j = 0;
		for (vj = c; vj <= d+Delta/2; vj += Delta)
		{
			matrix[i][j].value = f(ui, vj);
			matrix[i][j].u = ui;
			matrix[i][j].v = vj;
			//cout << matrix[i][j].value << " ";
			j++;
		}
		i++;
		//cout << endl;
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
