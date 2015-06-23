#include "ConstraintManager.h"

//helps initialize the ConstraintManager matrices
void ConstraintManager::initMats(std::vector<double> disps, std::vector<double> frcs)
{
	int temp = 0;
	std::vector<double> dspVec(dim);
	for(int i: dispLocs){
		dspVec[i] = disps[temp++];
	}
	temp = 0;
	std::vector<double> frcVec(dim);
	for(int i: frcLocs){
		frcVec[i] = frcs[temp++];
	}
	displacements = Matrix(dspVec, dim, 1);
	forces = Matrix(frcVec, dim, 1);
}

void ConstraintManager::addDeflections(Matrix deflections)
{
	int temp = 0;
	for(int i: frcLocs){
		displacements.setElement(i, deflections.getMatrix()[temp++]);
	}
}

//returns a displacement vector with force-defined dimensions eliminated
Matrix ConstraintManager::displacements_reduced()
{
	return MatrixManager::eliminate(displacements, frcLocs, std::vector<int>());
}

//returns a force vector with displacement-defined dimensions eliminated
Matrix ConstraintManager::forces_reduced()
{
	return MatrixManager::eliminate(forces, dispLocs, std::vector<int>());
}