#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "LuDecomposer.h"
#include <malloc.h>
#include <string.h>

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


void LuDecomposerTestOne(LuDecomposer decomposer)
{
	int size = 3;
	double *L, *U;
	double A[] = {
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

	L = new double[size * size]();
	U = new double[size * size]();

	decomposer.LU_Decomposition(A, L, U, size);

	bool isCorrect = decomposer.IsCorrectLU(A, L, U, size);

	if (isCorrect)
		printf("============= Success!\n");
	else
		printf("============= Error!\n");


	printf("============= Print L\n");
	decomposer.PrintMatrix(L, size);
	printf("============= Print U\n");
	decomposer.PrintMatrix(U, size);

}
