#ifndef MATRIX_MANAGER_H
#define MATRIX_MANAGER_H

#include <vector>
#include <iostream>
#include "Matrix.h"

namespace MatrixManager
{
	Matrix multMatrices(Matrix m1, Matrix m2);
	Matrix invert(Matrix matrix);
	Matrix eliminate(Matrix matrix, std::vector<int> rowMap, std::vector<int> colMap);
	std::vector<double> getRow(Matrix matrix, int n);
	std::vector<double> getCol(Matrix matrix, int n);
	double multRC(std::vector<double> row, std::vector<double> column);
	void print(Matrix matrix);
};

#endif