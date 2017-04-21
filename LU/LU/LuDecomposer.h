#pragma once
class LuDecomposer
{
public:
	LuDecomposer();
	~LuDecomposer();
	void LU_Decomposition(double * A, double * L, double * U, int N);
	void PrintMatrix(double *A, int n);
	bool IsCorrectLU(double *A, double *L, double *U, int size);
	bool AreEqual(double *a, double *b, int n);
	void Multiplication(double *A, double *B, double *Res, int size);

private: 
	const double DOUBLE_EPS = 0.00000001;

	void LU(double * A, double * L, double * U, int N, int subMatrixSize, int submatrixIndex);
};

