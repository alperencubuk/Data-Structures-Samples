#include <string>
#include <math.h>
#include <iostream>
using namespace std;

//////////////////////////////////////////////////////
//				Recursive Factorial
//////////////////////////////////////////////////////
int recursiveFactorial(int n)
{														
	if (n == 0) 
		return 1;										// basis case
	else 
		return n * recursiveFactorial(n-1);				// recursive case
}

/////////////////////////////////////////////////////
//					Linear Sum
/////////////////////////////////////////////////////
int linearSum(int A[], int n)
{
	if (n == 1) 
		return A[0];									// basis case
	else 
		return A[n-1] + linearSum(A, n-1);				// recursive case
}

/////////////////////////////////////////////////////
//					Reverse Array
/////////////////////////////////////////////////////
void reverseArray(int* A, int i, int j)
{
	if ( i<j )
	{
		int temp = A[j];
		A[j] = A[i];
		A[i] = temp;

		reverseArray( A, i+1, j-1);
	}
}

/////////////////////////////////////////////////////
//		Iterative Reverse Array (Tail Recursion)
/////////////////////////////////////////////////////
void iterativeReverseArray(int* A, int i, int j)
{
	while ( i<j )
	{
		int temp = A[j];
		A[j] = A[i];
		A[i] = temp;

		i = i+1;
		j = j-1;
	}	
}

/////////////////////////////////////////////////////
//					Binary Sum
/////////////////////////////////////////////////////
int binarySum(int A[], int i, int n)
{
	if (n == 1) 
		return A[i];
	else 
		return binarySum(A, i, n/2 ) + binarySum(A, i + n/2, n/2 );
}

/////////////////////////////////////////////////////
//					Binary Fibonacci
/////////////////////////////////////////////////////
int binaryFibonacci(int k)
{
	if (k <= 1) 
		return k;
	else 
		return binaryFibonacci(k-1) + binaryFibonacci(k-2);
}

/////////////////////////////////////////////////////
//					Linear Fibonacci
////////////////////////////////////////////////////
int linearFibonacci(int a, int b, int n)
{
	if (n <= 1) 
		return b;
	else 
		return linearFibonacci(b, a+b, n-1);
}

/////////////////////////////////////////////////////
//					Triple Sum
/////////////////////////////////////////////////////
int tripleSum(int A[], int i, int n)
{
	if (n == 1) 
		return A[i];
	else
	{
		int Sum = tripleSum(A, i, n / 3)
			+ tripleSum(A, i + n / 3, n / 3)
			+ tripleSum(A, i + 2 * n / 3, n / 3);
		cout << "Sum = " << Sum << endl;
		return Sum;
	}
}

/////////////////////////////////////////////////////
//						Ruler
////////////////////////////////////////////////////
void drawOneTick(int tickLength, int tickLabel = -1) {
	for (int i = 0; i < tickLength; i++)
	cout << "-";
	if (tickLabel >= 0) cout << " " << tickLabel;
	cout << "\n";
}

void drawTicks(int tickLength)
{													// draw ticks of given length
	if (tickLength > 0)
	{												// stop when length drops to 0
		drawTicks(tickLength-1);					// recursively draw left ticks
		drawOneTick(tickLength);					// draw center tick
		drawTicks(tickLength-1);					// recursively draw right ticks
	}
}

void drawRuler(int nInches, int majorLength)
{													// draw the entire ruler
	drawOneTick(majorLength, 0);					// draw tick 0 and its label
	for (int i = 1; i <= nInches; i++)
	{
		drawTicks(majorLength-1);					// draw ticks for this inch
		drawOneTick(majorLength, i);				// draw tick i and its label
	}
}


int main()
{
	int A[8] = {1,2,3,4,5,6,7,8};

	int factorial = recursiveFactorial(5);
	cout << "factorial(5) =  " << factorial << endl << endl;

	cout << "reverseArray =  ";
	reverseArray(A, 0, 7);				
	for (int i = 0; i<8; i++) cout << A[i] << " "; cout << "\n";	

	cout << "iterRevArray =  ";
	iterativeReverseArray(A, 0, 7);
	for (int i = 0; i<8; i++) cout << A[i] << " "; cout << "\n\n";

	int linSum = linearSum(A, 8);
	cout << "linearSum =  " << linSum << endl;

	int binSum = binarySum(A, 0, 8);
	cout << "binarySum =  " << binSum << endl << endl;

	int binFibonacci = binaryFibonacci(10);
	cout << "binaryFibonacci =  " << binFibonacci << endl;

	int linFibonacci = linearFibonacci(0, 1, 10);
	cout << "linearFibonacci =  " << linFibonacci << endl << endl;

	int B[27] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 };
	int tripSum = tripleSum(B, 0, 27);
	cout << "tripleSum =  " << tripSum << endl;

	::getchar();
}