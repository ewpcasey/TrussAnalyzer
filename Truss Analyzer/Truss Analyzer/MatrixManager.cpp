#include "MatrixManager.h"

namespace MatrixManager
{
	//multiplies two matrices
	Matrix MatrixManager::multMatrices(Matrix m1, Matrix m2)
	{
		Matrix toReturn(m1.getM(), m2.getN());
		for(int m = 0; m < m1.getM(); m++){
			for(int n = 0; n < m2.getN(); n++){
				toReturn.setElement(m * toReturn.getN() + n, multRC(getRow(m1, m), getCol(m2, n)));
			}
		}
		return toReturn;
	}

	//returns the inverse of passed matrix
	Matrix MatrixManager::invert(Matrix matrix)
	{
		int dim = matrix.getM();
		std::vector<double> matCopy(matrix.getMatrix());
		std::vector<double> inverse(matrix.getSize());
		for(int i = 0; i < dim; i++){
			inverse[i * dim + i] = 1;
		}
		for(int i = 0; i < dim; i++){
			double temp = matCopy[i * dim + i];
			for(int j = i * dim; j < i * dim + dim; j++){
				matCopy[j] = matCopy[j] / temp;
				inverse[j] = inverse[j] / temp;
			}
			for(int j = 0; j < matrix.getSize(); j += dim){
				temp = matCopy[j + i];
				for(int k = j; k < j + dim; k++){
					switch(i * dim - j){
					case 0:
						break;
					default:
						matCopy[k] = matCopy[k] - temp * matCopy[k - j + i * dim];
						inverse[k] = inverse[k] - temp * inverse[k - j + i * dim];
					}
				}
			}
		}
		return Matrix(inverse, matrix.getM(), matrix.getN());
	}

	//eliminates rows and columns of a matrix for reduced matrix calculations
	Matrix MatrixManager::eliminate(Matrix matrix, std::vector<int> rowElims, std::vector<int> colElims)
	{
		std::vector<int> rowMap(matrix.getM(), 1);
		std::vector<int> colMap(matrix.getN(), 1);
		for(int i: rowElims){
			rowMap[i] = 0;
		}
		for(int i: colElims){
			colMap[i] = 0;
		}
		int nM = matrix.getM() - rowElims.size();
		int nN = matrix.getN() - colElims.size();
		std::vector<double> toReturn(nM * nN);
		int count = 0;
		for(int i = 0; i < matrix.getSize(); i++){
			switch(colMap[i % matrix.getN()] * rowMap[i / matrix.getN()]){
			case 1:
				toReturn[count++] = matrix.getMatrix()[i];
			default:
				;
			}
		}
		return Matrix(toReturn, nM, nN);
	}

	//Gets values from row m of matrix
	std::vector<double> MatrixManager::getRow(Matrix matrix, int m)
	{
		std::vector<double> toReturn(matrix.getN());
		for(int i = 0; i < matrix.getN(); i++){
			toReturn[i] = matrix.getMatrix()[m * matrix.getN() + i];
		}
		return toReturn;
	}

	//Gets values from column n of matrix with size 'size'.
	std::vector<double> MatrixManager::getCol(Matrix matrix, int n)
	{
		std::vector<double> toReturn(matrix.getM());
		for(int i = 0; i < matrix.getM(); i++){
			toReturn[i] = matrix.getMatrix()[i * matrix.getN() + n];
		}
		return toReturn;
	}

	//Returns dot product of two vectors--used for row * colum in matrix multiplication
	double MatrixManager::multRC(std::vector<double> row, std::vector<double> column)
	{
		double sum = 0;
		for(unsigned int i = 0; i < row.size(); i++){
			sum += row[i] * column[i];
		}
		return sum;
	}

	//prints the values of the matrix
	void MatrixManager::print(Matrix matrix)
	{
		for(int i = 0; i < matrix.getM() * matrix.getN(); i++){
			std::cout << matrix.getMatrix()[i];
			switch(matrix.getN() - (i % matrix.getN())){
			case 1:
				std::cout << "\n";
				break;
			default:
				std::cout << "\t";
			}
		}
		std::cout << "\n";
	}
}