#pragma once
#include "LuDecomposer.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
class LuTests
{
public:
	LuTests();
	LuTests(LuDecomposer *_decomposer);
	~LuTests();

	void LuDecomposerTestOne();
	void LuDecomposerTestTwo();
	void LuDecomposerTest3();
	void SolveRightUpperBlockTestOne();
	void SolveRightUpperBlockTestTwo();
	void SolveRightUpperBlockTestForNonSquareMatrix();
	void SolveLeftLowerBlockTestNonSquareMatrix();
	void SolveLeftLowerBlockTestOne();
	void SolveLeftLowerBlockTestTwo();
	void MaltiplicationTestOne();
	void MaltiplicationTestTwo();
	void LuDecompositionOfRandomMatrix(int size);


private:
	LuDecomposer *decomposer;
	void GenerateArray(double *a, int size);
	void CopyArray(double *a, double *b, int size);
};

