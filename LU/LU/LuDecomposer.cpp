#include "LuDecomposer.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include <omp.h> 

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
* A - �������� ������� 
* L, U - �������, ������� ���������� � ���������� ����������
* N - ������ �������� ������� �
*/
void LuDecomposer::LU_Decomposition(double * A, double * L, double * U, int N)
{
	int blockCount = N / BlockSize;
	int currMatrixSize = N;

	for (int i = 0; i <= blockCount; i++)
	{
		if (currMatrixSize - BlockSize <= 0)
		{
			LU(A, L, U, N, currMatrixSize, i * BlockSize, i * BlockSize);
			break;
		}

		LU(A, L, U, N, BlockSize, i * BlockSize, i * BlockSize);

		SolveRightUpperBlock(A, L, U, N, BlockSize, currMatrixSize - BlockSize, i * BlockSize, i * BlockSize, i * BlockSize, (i + 1) * BlockSize);

		SolveLeftLowerBlock(A, L, U, N, currMatrixSize - BlockSize, BlockSize, (i + 1) * BlockSize, i * BlockSize, i * BlockSize, i * BlockSize);

		double *L21U12 = new double[(currMatrixSize - BlockSize) * (currMatrixSize - BlockSize)]();
		Multiplication(L, U, L21U12, N, currMatrixSize - BlockSize, BlockSize, (i + 1) * BlockSize, i * BlockSize, i * BlockSize, (i + 1) * BlockSize);

		Diff(A, L21U12, N, currMatrixSize - BlockSize, (i + 1) * BlockSize, (i + 1) * BlockSize);

		currMatrixSize = currMatrixSize - BlockSize;

		delete[] L21U12;
	}

	//LU(A, L, U, N, N, 0, 0);
}

/*
* ����� ��������� ���������������� �������� LU ����������
* �������� ���������� � ������� �.
*
* A - �������� �������
* L, U - �������, ������� ���������� � ���������� ����������
* N - ������ �������� ������� �
* subMatrixSize - ������ ����������, ��� ������� ����� ���������� ����������
* rowBias - �������� ���������� �� �������
* colBias - �������� ������� �� ��������
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
	int _size = size * size;
	double *LU = new double[_size]();

	Multiplication(L, U, LU, size, size, size, 0, 0, 0, 0);
	
	bool res = AreEqual(A, LU, size);
	if (!res)
	{
		printf("============= Print L * U\n");
		PrintMatrix(LU, size);
	}

	delete[] LU;
	LU = NULL;

	return res;
}


bool LuDecomposer::AreEqual(double *a, double *b, int n)
{
	for (int i = 0; i < n * n; i++)
	{
		if (abs(a[i] - b[i]) > DOUBLE_EPS)
		{
			return false;
		}
	}

	return true;
}

void LuDecomposer::Multiplication(double *A, double *B, double *Res, int size, int subMatrixHeight, int subMatrixWidth, int rowBiasA, int colBiasA, int rowBiasB, int colBiasB)
{
	int u, v, p;
	#pragma omp parallel private(u, v, p)
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

	#pragma omp parallel private(sum)
	{
		int m, n, r;
		int coo1 = colBiasU + rowBiasU * N;
		int coo2 = rowBiasL * N + colBiasL;

		// ���� �� �������� ������� �
		#pragma omp for 
		for (int j = 0; j < subMatrixWidth; j++)
		{
			n = j + coo1;

			// ���� �� �������� L
			for (int i = 0; i < subMatrixHeight; i++)
			{
				m = i * N + coo2;
				sum = 0;
				#pragma simd
				for (int k = 0; k < i; k++)
				{
					sum += U[k * N  + n] * L[m + k];
				}

				U[i * N + n] = A[i * N + n] - sum;
			}
		}
	}
}

void LuDecomposer::SolveLeftLowerBlock(double * A, double * L, double * U, int N, int subMatrixHeight, int subMatrixWidth, int rowBiasL, int colBiasL, int rowBiasU, int colBiasU)
{
	double sum;
	#pragma omp parallel private(sum)
	{
		int m, n, r;
		int coo1 = rowBiasU * N + colBiasU;
		int coo2 = rowBiasL * N + colBiasL;
		// ���� �� ������� ������� �
		#pragma omp for 
		for (int j = 0; j < subMatrixHeight; j++)
		{
			m = j * N + coo2;

			// ���� �� �������� ������� U
			for (int i = 0; i < subMatrixWidth; i++)
			{
				n = coo1 + i;
				sum = 0;
				#pragma simd
				for (int k = 0; k < i; k++)
				{
					sum += U[k * N + n] * L[k + m];
				}

				L[m + i] = (A[m + i] - sum) / U[i * N + n];
			}
		}
	}
}

void LuDecomposer::Diff(double *A, double *B, int N, int subMatrixSize, int rowBias, int colBias)
{
	#pragma omp parallel
	{
		int m, n;
		int coo = rowBias * N + colBias;
		#pragma omp for 
		for (int i = 0; i < subMatrixSize; i++)
		{
			m = i * subMatrixSize;
			n = i * N + coo;
			for (int j = 0; j < subMatrixSize; j++)
			{
				A[j + n] -= B[m + j];
			}
		}
	}
}


