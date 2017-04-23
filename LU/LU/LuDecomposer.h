#pragma once

class LuDecomposer
{
public:
	LuDecomposer();
	LuDecomposer(int blockSize);
	~LuDecomposer();
	void LU_Decomposition(double * A, double * L, double * U, int N);
	void PrintMatrix(double *A, int n);
	bool IsCorrectLU(double *A, double *L, double *U, int size);
	bool AreEqual(double *a, double *b, int n);
	void Multiplication(double *A, double *B, double *Res, int size, int subMatrixHeight, int subMatrixWidth, int rowBiasA, int colBiasA, int rowBiasB, int colBiasB);
	void SolveRightUpperBlock(double * A, double * L, double * U, int N, int subMatrixHeight, int subMatrixWidth, int rowBiasL, int colBiasL, int rowBiasU, int colBiasU);
	void SolveLeftLowerBlock(double * A, double * L, double * U, int N, int subMatrixHeight, int subMatrixWidth, int rowBiasL, int colBiasL, int rowBiasU, int colBiasU);
	void LU(double * A, double * L, double * U, int N, int subMatrixSize, int rowBias, int colBias);

private: 
	const double DOUBLE_EPS = 0.00000001;
	int BlockSize = 3;

	void Diff(double *A, double *B, int N, int subMatrixSize, int rowBias, int colBias);
};

