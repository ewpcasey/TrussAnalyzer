#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
public:
	Matrix():
		m(0), n(0), size(0), matrix() {};
	Matrix(int m, int n): 
		m(m), n(n), size(n * m), matrix(size) {};
	Matrix(std::vector<double> matrix, int m, int n):
		m(m), n(n), size(n * m), matrix(matrix) {};
	Matrix(const Matrix& src):
		n(src.n), m(src.m), size(src.size), matrix(src.matrix.size())
	{
		for(int i = 0; i < matrix.size(); i++){
			matrix[i] = src.matrix[i];
		}
	};
	
	std::vector<double> getMatrix() {return matrix;};
	int getN() {return n;};
	int getM() {return m;};
	int getSize() {return size;}
	
	void setElement(int n, double val) {matrix[n] = val;};
	void setElement(int nM, int nN, double val) {setElement(nM * n + nN, val);};

private:
	int n;
	int m;
	int size;

	std::vector<double> matrix;
};

#endif