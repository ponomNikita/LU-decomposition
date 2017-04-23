#pragma once
#include "LuDecomposer.h"
#include "stdio.h"
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


private:
	LuDecomposer *decomposer;
};

