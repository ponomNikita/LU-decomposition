#include "LuDecomposer.h"
#include "stdio.h"
#include "math.h"

LuDecomposer::LuDecomposer()
{
}

LuDecomposer::LuDecomposer(int blockSize)
{
	BlockSize = blockSize;
}

LuDecomposer::~LuDecomposer()
{
}


/*
* A - исходная матрица 
* L, U - матрицы, которые получаются в результате разложения
* N - размер исходной матрицы А
*/
void LuDecomposer::LU_Decomposition(double * A, double * L, double * U, int N)
{
	int blockCount = N / BlockSize;
	int currMatrixSize = N;

	for (int i = 0; i <= blockCount; i++)
	{
	/*	if (currMatrixSize - BlockSize <= 0)
		{
			LU(A, L, U, N, BlockSize, i * BlockSize, i * BlockSize);
			break;
		}

		LU(A, L, U, N, BlockSize, i * BlockSize, i * BlockSize);

		SolveRightUpperBlock(A, L, U, N, BlockSize, currMatrixSize - BlockSize, i * BlockSize, (i + 1) * BlockSize);

		SolveLeftLowerBlock(A, L, U, N, currMatrixSize - BlockSize, BlockSize, (i + 1) * BlockSize, i * BlockSize);

		double *L21U12 = new double[(currMatrixSize - BlockSize) * (currMatrixSize - BlockSize)]();
		Multiplication(L, U, L21U12, N, currMatrixSize - BlockSize, BlockSize, (i + 1) * BlockSize, i * BlockSize, i * BlockSize, (i + 1) * BlockSize);

		Diff(A, L21U12, currMatrixSize - BlockSize, (i + 1) * BlockSize, (i + 1) * BlockSize);

		currMatrixSize = currMatrixSize - BlockSize;*/
	}

	LU(A, L, U, N, N, 0, 0);
}

/*
* Метод выполняет последовательный алгоритм LU разложения
* заданной подматрицы в массиве А.
*
* A - исходная матрица
* L, U - матрицы, которые получаются в результате разложения
* N - размер исходной матрицы А
* subMatrixSize - размер подматрицы, для которой будет проводится разложение
* rowBias - смещение подматрицы по строкам
* colBias - смещение матрицы по столбцам
*/
void LuDecomposer::LU(double * A, double * L, double * U, int N, int subMatrixSize, int rowBias, int colBias)
{
	double sum;

	for (int i = 0; i < subMatrixSize; i++)
	{
		L[(i + rowBias) * N + (i + colBias)] = 1;
		for (int j = i; j < subMatrixSize; j++)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += L[(i + rowBias) * N + (k + colBias)] * U[(k + rowBias) * N + (j + colBias)];
			}
			U[(i + rowBias) * N + (j + colBias)] = A[(i + rowBias) * N + (j + colBias)] - sum;
		}
		for (int j = i + 1; j < subMatrixSize; j++)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += L[(j + rowBias) * N + (k + colBias)] * U[(k + rowBias) * N + (i + colBias)];
			}
			L[(j + rowBias) * N + (i + colBias)] = (A[(j + rowBias) * N + (i + colBias)] - sum) / U[(i + rowBias) * N + (i + colBias)];
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
	Multiplication(L, U, LU, size, size, size, 0, 0, 0, 0);
	
	bool res = AreEqual(A, LU, size);
	if (!res)
	{
		printf("============= Print L * U\n");
		PrintMatrix(LU, size);
	}

	delete[] LU;

	return res;
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

void LuDecomposer::Multiplication(double *A, double *B, double *Res, int size, int subMatrixHeight, int subMatrixWidth, int rowBiasA, int colBiasA, int rowBiasB, int colBiasB)
{
	int u, v, p;
	#pragma omp parallel  num_threads(threadCount)	
	{
		#pragma omp for 
		for (int i = 0; i < subMatrixHeight; i++)
		{
			u = (i + rowBiasA) * size + colBiasA;
			for (int j = 0; j < subMatrixWidth; j++)
			{
				v = (j + rowBiasB) * size + colBiasB;
				p = u + j;

				#pragma simd
				for (int t = 0; t < subMatrixHeight; t++)
				{
					Res[i * subMatrixHeight + t] += A[p] * B[v + t];
				}
			}
		}
	}
}

void LuDecomposer::SolveRightUpperBlock(double * A, double * L, double * U, int N, int subMatrixHeight, int subMatrixWidth, int rowBiasL, int colBiasL, int rowBiasU, int colBiasU)
{
	double sum;

	// Цикл по столбцам матрицы А
	for (int j = 0; j < subMatrixWidth; j++)
	{
		// Цикл по строчкам L
		for (int i = 0; i < subMatrixHeight; i++)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += U[(k + rowBiasU) * N + j + colBiasU] * L[(i + rowBiasL) * N + k + colBiasL];
			}

			U[(i + rowBiasU) * N + j + colBiasU] = A[(i + rowBiasU) * N + j + colBiasU] - sum;
		}
	}
}

void LuDecomposer::SolveLeftLowerBlock(double * A, double * L, double * U, int N, int subMatrixHeight, int subMatrixWidth, int rowBiasL, int colBiasL, int rowBiasU, int colBiasU)
{
	double sum;

	// Цикл по строчка матрицы А
	for (int j = 0; j < subMatrixHeight; j++)
	{
		// Цикл по столбцам матрицы U
		for (int i = 0; i < subMatrixWidth; i++)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += U[(k + rowBiasU) * N + i + colBiasU] * L[(j + rowBiasL) * N + k + colBiasL];
			}

			L[(j + rowBiasL) * N + i + colBiasL] = (A[(j + rowBiasL) * N + i + colBiasL] - sum) / U[(i + rowBiasU) * N + i + colBiasU];
		}
	}
}

void LuDecomposer::Diff(double *A, double *B, int subMatrixSize, int rowBias, int colBias)
{
	for (int i = 0; i < subMatrixSize; i++)
	{
		for (int j = 0; j < subMatrixSize; j++)
		{
			A[(i + rowBias) * subMatrixSize + j + colBias] -= B[i * subMatrixSize + j];
		}
	}
}


