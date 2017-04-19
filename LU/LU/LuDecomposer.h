#pragma once
class LuDecomposer
{
public:
	LuDecomposer();
	~LuDecomposer();
	void LU_Decomposition(double * A, double * L, double * U, int N);

private: 
	void LU(double * A, double * L, double * U, int N);
};

