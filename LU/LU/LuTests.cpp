#include "LuTests.h"


LuTests::LuTests()
{
}

LuTests::LuTests(LuDecomposer *_decomposer)
{
	decomposer = _decomposer;
}

LuTests::~LuTests()
{
}




void LuTests::LuDecomposerTestOne()
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

	decomposer->LU_Decomposition(A, L, U, size);

	bool isCorrect = decomposer->IsCorrectLU(A, L, U, size);

	if (isCorrect)
		printf("============= Success!\n");
	else
		printf("============= Error!\n");


	if (!isCorrect)
	{
		printf("============= Print L\n");
		decomposer->PrintMatrix(L, size);
		printf("============= Print U\n");
		decomposer->PrintMatrix(U, size);
	}

	delete[] L, U, A;
}

void LuTests::LuDecomposerTestTwo()
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

	decomposer->LU_Decomposition(A, L, U, size);

	bool isCorrect = decomposer->IsCorrectLU(A, L, U, size);

	if (isCorrect)
		printf("============= Success!\n");
	else
		printf("============= Error!\n");

	if (!isCorrect)
	{
		printf("============= Print L\n");
		decomposer->PrintMatrix(L, size);
		printf("============= Print U\n");
		decomposer->PrintMatrix(U, size);
	}

	delete[] L, U, A;
}

void LuTests::SolveRightUpperBlockTestOne()
{
	int size = 3;
	double A[] = {
		1, 0, 1,
		0, 1, 1,
		1, 0, 2
	};

	double L[] = {
		1, 0, 0,
		2, 1, 0,
		3, 4, 1
	};

	double *U = new double[size * size]();

	double expectedU[] = {
		1, 0, 1,
		-2, 1, -1,
		6, -4, 3
	};

	decomposer->SolveRightUpperBlock(A, L, U, size, size, size, 0, 0, 0, 0);

	bool isCorrect = decomposer->AreEqual(U, expectedU, size);

	if (isCorrect)
		printf("============= Success!\n");
	else
	{
		printf("============= Error!\n");
		printf("============= Print U\n");
		decomposer->PrintMatrix(U, size);
	}
}

void LuTests::SolveRightUpperBlockTestTwo()
{
	int size = 5;
	double A[] = {
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 1,
		0, 0, 0, 1, 1,
		0, 0, 1, 0, 2,
		0, 0, 0, 0, 0
	};

	double L[] = {
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 2, 1, 0,
		0, 0, 3, 4, 1,
		0, 0, 0, 0, 0
	};

	double *U = new double[size * size]();

	double expectedU[] = {
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 1,
		0, 0, -2, 1, -1,
		0, 0, 6, -4, 3,
		0, 0, 0, 0, 0
	};

	decomposer->SolveRightUpperBlock(A, L, U, size, 3, 3, 1, 2, 1, 2);

	bool isCorrect = decomposer->AreEqual(U, expectedU, size);

	if (isCorrect)
		printf("============= Success!\n");
	else
	{
		printf("============= Error!\n");
		printf("============= Print U\n");
		decomposer->PrintMatrix(U, size);
	}
}

void LuTests::SolveLeftLowerBlockTestOne()
{
	int size = 3;
	double A[] = {
		1, 0, 1,
		0, 1, 1,
		1, 0, 2
	};

	double U[] = {
		1, 2, 3,
		0, 1, 4,
		0, 0, 2
	};

	double *L = new double[size * size]();

	double expectedL[] = {
		1, -2, 3,
		0, 1, -1.5,
		1, -2, 3.5
	};

	decomposer->SolveLeftLowerBlock(A, L, U, size, size, size, 0, 0, 0, 0);

	bool isCorrect = decomposer->AreEqual(L, expectedL, size);

	if (isCorrect)
		printf("============= Success!\n");
	else
	{
		printf("============= Error!\n");
		printf("============= Print U\n");
		decomposer->PrintMatrix(U, size);
	}
}

void LuTests::SolveLeftLowerBlockTestTwo()
{
	int size = 5;
	double A[] = {
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 1,
		0, 0, 0, 1, 1,
		0, 0, 1, 0, 2,
		0, 0, 0, 0, 0
	};

	double U[] = {
		0, 0, 0, 0, 0,
		0, 0, 1, 2, 3,
		0, 0, 0, 1, 4,
		0, 0, 0, 0, 2,
		0, 0, 0, 0, 0
	};

	double *L = new double[size * size]();

	double expectedL[] = {
		0, 0, 0, 0, 0,
		0, 0, 1, -2, 3,
		0, 0, 0,  1, -1.5,
		0, 0, 1, -2, 3.5,
		0, 0, 0, 0, 0
	};

	decomposer->SolveLeftLowerBlock(A, L, U, size, 3, 3, 1, 2, 1, 2);

	bool isCorrect = decomposer->AreEqual(L, expectedL, size);

	if (isCorrect)
		printf("============= Success!\n");
	else
	{
		printf("============= Error!\n");
		printf("============= Print L\n");
		decomposer->PrintMatrix(L, size);
	}
}

void LuTests::MaltiplicationTestOne()
{
	double A[] = {
		1, 2, 0,
		3, 4, 0,
		5, 6, 0
	};

	double B[] = {
		1, 3, 5,
		2, 4, 6,
		0, 0, 0
	};

	double expectedAA[] = {
		5, 11, 17,
		11, 25, 39,
		17, 39, 61
	};

	double *AA = new double[9]();

	decomposer->Multiplication(A, B, AA, 3, 3, 2, 0, 0, 0, 0);

	bool isCorrect = decomposer->AreEqual(AA, expectedAA, 3);

	if (isCorrect)
		printf("============= Success!\n");
	else
	{
		printf("============= Error!\n");
		printf("============= Print AA\n");
		decomposer->PrintMatrix(AA, 3);
	}
}

void LuTests::MaltiplicationTestTwo()
{
	double A[] = {
		0, 0, 0, 0, 0,
		0, 0, 1, 2, 0,
		0, 0, 3, 4, 0,
		0, 0, 5, 6, 0,
		0, 0, 0, 0, 0
	};

	double B[] = {
		0, 0, 0, 0, 0,
		0, 0, 1, 3, 5,
		0, 0, 2, 4, 6,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	};

	double expectedAA[] = {
		5, 11, 17,
		11, 25, 39,
		17, 39, 61
	};

	double *AA = new double[9]();

	decomposer->Multiplication(A, B, AA, 5, 3, 2, 1, 2, 1, 2);

	bool isCorrect = decomposer->AreEqual(AA, expectedAA, 3);

	if (isCorrect)
		printf("============= Success!\n");
	else
	{
		printf("============= Error!\n");
		printf("============= Print AA\n");
		decomposer->PrintMatrix(AA, 3);
	}
}

void LuTests::SolveRightUpperBlockTestForNonSquareMatrix()
{
	int size = 5;
	double A[] = {
		0, 0, 0, 0, 0,
		0, 0, 2, 1, 2,
		0, 0, 1, 2, 1,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	};

	double L[] = {
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0
	};

	double *U = new double[size * size]();

	double expectedU[] = {
		0, 0, 0, 0, 0,
		0, 0, 2, 1, 2,
		0, 0, -1, 1, -1,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	};

	decomposer->SolveRightUpperBlock(A, L, U, size, 2, 3, 2, 1, 1, 2);

	bool isCorrect = decomposer->AreEqual(U, expectedU, size);

	if (isCorrect)
		printf("============= Success!\n");
	else
	{
		printf("============= Error!\n");
		printf("============= Print U\n");
		decomposer->PrintMatrix(U, size);
	}
}
