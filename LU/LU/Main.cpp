#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "LuDecomposer.h"
#include <malloc.h>
#include <string.h>

void LuDecomposerTestOne(LuDecomposer decomposer);
void LuDecomposerTestTwo(LuDecomposer decomposer);


int main()
{
	LuDecomposer decomposer;

	printf("============= Runing tests\n");

	printf("============= Tets 1\n");
	LuDecomposerTestOne(decomposer);

	printf("============= Tets 2\n");
	LuDecomposerTestTwo(decomposer);

	_getch();
	return 0;
}


void LuDecomposerTestOne(LuDecomposer decomposer)
{
	int size = 3;
	double *L, *U;
	double A[] = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
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

void LuDecomposerTestTwo(LuDecomposer decomposer)
{
	int size = 5;
	double *L, *U;
	double A[] = {
		1, 2, 3, 9, 5,
		6, 3, 8, 9, 10,
		11, 5, 7, 34, 15,
		16, 17, 1, 19, 20,
		21, 22, 4, 24, 25
	};

	L = new double[size * size]();
	U = new double[size * size]();

	decomposer.LU_Decomposition(A, L, U, size);

	printf("============= Print L\n");
	decomposer.PrintMatrix(L, size);
	printf("============= Print U\n");
	decomposer.PrintMatrix(U, size);

	bool isCorrect = decomposer.IsCorrectLU(A, L, U, size);

	if (isCorrect)
		printf("============= Success!\n");
	else
		printf("============= Error!\n");
}
