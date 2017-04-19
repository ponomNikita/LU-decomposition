#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "LuDecomposer.h"
#include <malloc.h>


const double DOUBLE_EPS = 0.00000001;

bool AreEqual(double *a, double *b, int n);
void LuDecomposerTestOne(LuDecomposer decomposer);

int main()
{
	LuDecomposer decomposer;

	printf("============= Runing tests\n");
	printf("============= Tets 1\n");
	LuDecomposerTestOne(decomposer);

	_getch();
	return 0;
}

bool AreEqual(double *a, double *b, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (abs(a[i] - b[i]) > DOUBLE_EPS)
			return false;
	}

	return true;
}

void LuDecomposerTestOne(LuDecomposer decomposer)
{
	int size = 9;
	double *L, *U;
	double *A = new double[]{
		1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	double expectedL[] = {
			1.000, 0.000, 0.000,
			0.143, 1.000, 0.000,
			0.571, 0.500, 1.000
	};

	double expectedU[] = {
			7.000, 8.000, 9.000,
			0.000, 0.857, 1.714,
			0.000, 0.000, 0.000
	};

	L = (double*)_mm_malloc(size*sizeof(double), 32);
	U = (double*)_mm_malloc(size*sizeof(double), 32);

	decomposer.LU_Decomposition(A, L, U, size);

	if (!AreEqual(L, expectedL, size))
	{
		printf("============= L is not correct\n");
	}
	else if (!AreEqual(U, expectedU, size))
	{
		printf("============= U is not correct\n");
	}
	else{
		printf("============= Success!\n");
	}

	_mm_free(L);
	_mm_free(U);
}