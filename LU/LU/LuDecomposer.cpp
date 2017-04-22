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
* A - �������� ������� 
* L, U - �������, ������� ���������� � ���������� ����������
* N - ������ �������� ������� �
*/
void LuDecomposer::LU_Decomposition(double * A, double * L, double * U, int N)
{
	int blockCount = N / BlockSize;

	for (int i = 0; i < blockCount; i++)
	{

	}

	LU(A, L, U, N, N, 0, 0);
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
	double *LU = new double[size * size]();
	Multiplication(L, U, LU, size, size, 0, 0);
	
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

void LuDecomposer::Multiplication(double *A, double *B, double *Res, int size, int subMatrixSize, int rowBias, int colBias)
{
	int u, v, p;
	#pragma omp parallel  num_threads(threadCount)	
	{
		#pragma omp for 
		for (int i = 0; i < subMatrixSize; i++)
		{
			u = (i + rowBias) * size + colBias;
			for (int j = 0; j < subMatrixSize; j++)
			{
				v = (j + rowBias) * size + colBias;
				p = u + j;

				#pragma simd
				for (int t = 0; t < subMatrixSize; t++)
				{
					Res[u + t] += A[p] * B[v + t];
				}
			}
		}
	}
}

void LuDecomposer::SolveRightUpperBlock(double * A, double * L, double * U, int N, int subMatrixSize, int rowBias, int colBias)
{
	double sum;

	// ���� �� �������� ������� �
	for (int j = 0; j < subMatrixSize; j++)
	{
		// ���� �� �������� L
		for (int i = 0; i < subMatrixSize; i++)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += U[(k + rowBias) * N + j + colBias] * L[(i + rowBias) * N + k + colBias];
			}

			U[(i + rowBias) * N + j + colBias] = A[(i + rowBias) * N + j + colBias] - sum;
		}
	}
}

void LuDecomposer::SolveLeftLowerBlock(double * A, double * L, double * U, int N, int subMatrixSize, int rowBias, int colBias)
{
	double sum;

	// ���� �� ������� ������� �
	for (int j = 0; j < subMatrixSize; j++)
	{
		// ���� �� �������� ������� U
		for (int i = 0; i < subMatrixSize; i++)
		{
			sum = 0;
			for (int k = 0; k < i; k++)
			{
				sum += U[(k + rowBias) * N + i + colBias] * L[(j + rowBias) * N + k + colBias];
			}

			L[(j + rowBias) * N + i + colBias] = (A[(j + rowBias) * N + i + colBias] - sum) / U[(i + rowBias) * N + i + colBias];
		}
	}
}

