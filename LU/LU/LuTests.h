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
	void SolveRightUpperBlockTestOne();
	void SolveRightUpperBlockTestTwo();

private:
	LuDecomposer *decomposer;
};

