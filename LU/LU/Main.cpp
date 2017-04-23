#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "LuDecomposer.h"
#include <malloc.h>
#include <string.h>
#include "LuTests.h"

int main()
{
	LuDecomposer decomposer;
	LuTests tests(&decomposer);

	printf("============= Runing tests\n");

	printf("============= LuDecomposerTestOne\n");
	tests.LuDecomposerTestOne();

	printf("============= LuDecomposerTestTwo\n");
	tests.LuDecomposerTestTwo();

	printf("============= LuDecomposerTest3\n");
	tests.LuDecomposerTest3();

	printf("============= SolveRightUpperBlockTestOne\n");
	tests.SolveRightUpperBlockTestOne();

	printf("============= SolveRightUpperBlockTestTwo\n");
	tests.SolveRightUpperBlockTestTwo();

	printf("============= SolveLeftLowerBlockTestOne\n");
	tests.SolveLeftLowerBlockTestOne();

	printf("============= SolveLeftLowerBlockTestTwo\n");
	tests.SolveLeftLowerBlockTestTwo();

	printf("============= MaltiplicationTestOne\n");
	tests.MaltiplicationTestOne();

	printf("=============MaltiplicationTestTwo\n");
	tests.MaltiplicationTestTwo();

	printf("=============SolveRightUpperBlockTestForNonSquareMatrix\n");
	tests.SolveRightUpperBlockTestForNonSquareMatrix();

	printf("=============SolveLeftLowerBlockTestNonSquareMatrix\n");
	tests.SolveLeftLowerBlockTestNonSquareMatrix();

	printf("=============LuDecompositionOfRandomMatrix\n");
	tests.LuDecompositionOfRandomMatrix(1000);

	_getch();
	return 0;
}


