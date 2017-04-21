#include "LuDecomposer.h"
#include "stdio.h"
#include "math.h"

LuDecomposer::LuDecomposer()
{
}


LuDecomposer::~LuDecomposer()
{
}

/*
* A - исходна€ матрица 
* L, U - матрицы, которые получаютс€ в результате разложени€
* N - размер исходной матрицы ј
*/
void LuDecomposer::LU_Decomposition(double * A, double * L, double * U, int N)
{
	LU(A, L, U, N, N, 0);
}

/*
* ћетод выполн€ет последовательный алгоритм LU разложени€
* заданной подматрицы в массиве ј.
*
* A - исходна€ матрица
* L, U - матрицы, которые получаютс€ в результате разложени€
* N - размер исходной матрицы ј
* subMatrixSize - размер подматрицы, дл€ которой будет проводитс€ разложение
* submatrixIndex - индекс с которого начинаетс€ подматрица
*/
void LuDecomposer::LU(double * A, double * L, double * U, int N, int subMatrixSize, int submatrixIndex)
{
	double sum;

	for (int i = 0; i < N; i++)
	{
		L[i * N + i] = 1;
		for (int j = i; j < N; j++)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += L[i * N + k] * U[k * N + j];
			}
			U[i * N + j] = A[i * N + j] - sum;
		}
		for (int j = i + 1; j < N; j++)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += L[j * N + k] * U[k * N + i];
			}
			L[j * N + i] = (A[j * N + i] - sum) / U[i * N + i];
		}
	}
	
}

void LuDecomposer::PrintMatrix(double *A, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%f ", A[i * n + j]);
		}

		printf("\n");
	}
}

bool LuDecomposer::IsCorrectLU(double *A, double *L, double *U, int size)
{
	double *LU = new double[size * size]();
	Multiplication(L, U, LU, size);

	printf("============= Print L * U\n");
	PrintMatrix(LU, size);
	
	return AreEqual(A, LU, size);
}


bool LuDecomposer::AreEqual(double *a, double *b, int n)
{
	for (int i = 0; i < n * n; i++)
	{
		if (abs(a[i] - b[i]) > DOUBLE_EPS)
			return false;
	}

	return true;
}

void LuDecomposer::Multiplication(double *A, double *B, double *Res, int size)
{
	int u, v, p;
	#pragma omp parallel  num_threads(threadCount)	
	{
		#pragma omp for 
		for (int i = 0; i < size; i++) 
		{
			u = i * size;
			for (int j = 0; j < size; j++)
			{
				v = j * size;
				p = u + j;

				#pragma simd
				for (int t = 0; t < size; t++)
				{
					Res[u + t] += A[p] * B[v + t];
				}
			}
		}
	}
}
