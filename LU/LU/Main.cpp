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

	printf("============= Tets 1\n");
	tests.LuDecomposerTestOne();

	printf("============= Tets 2\n");
	tests.LuDecomposerTestTwo();

	printf("============= Tets 3\n");
	tests.SolveRightUpperBlockTestOne();

	printf("============= Tets 4\n");
	tests.SolveRightUpperBlockTestTwo();

	printf("============= Tets 5\n");
	tests.SolveLeftLowerBlockTestOne();

	printf("============= Tets 6\n");
	tests.SolveLeftLowerBlockTestTwo();

	printf("============= Tets 7\n");
	tests.MaltiplicationTestOne();

	printf("============= Tets 8\n");
	tests.MaltiplicationTestTwo();

	_getch();
	return 0;
}


