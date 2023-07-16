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

double f(double u, double v);
bool check_specific_point(double u, double v);

void find_minimax(void);
void find_maximin(void);

ofstream wrMinimax;
ofstream wrMaximin;

int main()
{
	startTime = clock();
	cout << fixed;
	cout.precision(3);

	a = 1.0;
	b = 11.0;
	N = 100;
	delta = (b - a) / double(N);
	cout << "a = " << a << " b = " << b << " delta = " << delta << endl;
	
	c = 1.0;
	d = 11.0;
	K = 100;
	Delta = (d - c) / double(K);
	cout << "c = " << c << " d = " << d << " Delta = " << Delta << endl << endl;

	wrMinimax.open("minimax.txt");
	wrMaximin.open("maximin.txt");
	if ((wrMinimax.is_open()) && (wrMaximin.is_open()))
	{
		do
		{
			find_minimax();
			find_maximin();
			a -= delta;
		} while (a >= -11.0);

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

bool check_specific_point(double u, double v)
{
	if (round(100.0*(u + v)) == 0)
		return false;
	else
		return true;
}

double f(double u, double v)
{	
	double initresult = (u - v) / (u + v);
	double result = initresult;
	int power = 4;

	for (int i = 0; i < power - 1; i++)
	{
		result *= initresult;
	}

	return result;
}

void find_minimax(void)
{
	pointInstance localMax;
	double localResult = 0.0;
	double ui = a, vj = c;
	int allMaxCounter = 0;
	bool isStarted = false;
	double initvj = 0.0;

	for (ui = a; ui <= b; ui += delta)
	{
		isStarted = false;
		vj = c;
		while (!isStarted)
		{
			if (check_specific_point(ui, vj))
			{
				localMax.value = f(ui, vj);
				localMax.u = ui;
				localMax.v = vj;
				isStarted = true;

				initvj = vj;
			}
			else
				vj += Delta;
		}

		for (vj = initvj; vj <= d; vj += Delta)
		{
			if (check_specific_point(ui, vj))
				localResult = f(ui, vj);
			else
				continue;
			
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
}

void find_maximin(void)
{
	pointInstance localMin;
	double localResult = 0;
	double ui = a, vj = c;
	int allMinCounter = 0;
	bool isStarted = false;
	double initui = 0.0;

	for (vj = c; vj <= d; vj += Delta)
	{
		isStarted = false;
		ui = a;
		while (!isStarted)
		{
			if (check_specific_point(ui, vj))
			{
				localMin.value = f(ui, vj);
				localMin.u = ui;
				localMin.v = vj;
				isStarted = true;

				initui = ui;
			}
			else
				ui += delta;
		}

		for (ui = initui; ui <= b; ui += delta)
		{
			if (check_specific_point(ui, vj))
				localResult = f(ui, vj);
			else
				continue;

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
