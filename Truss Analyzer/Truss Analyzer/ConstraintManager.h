#ifndef CONSTRAINTMANAGER_H
#define CONSTRAINTMANAGER_H

#include <vector>
#include "MatrixManager.h"

class ConstraintManager
{
public:
	ConstraintManager(int n, std::vector<int> dispLocs, std::vector<int> frcLocs, std::vector<double> disps, std::vector<double> frcs):
		dim(n), dispLocs(dispLocs), frcLocs(frcLocs) {initMats(disps, frcs);};
	ConstraintManager(const ConstraintManager& src):
		dim(src.dim), dispLocs(src.dispLocs.size()), frcLocs(src.frcLocs.size()), displacements(src.displacements), forces(src.forces)
	{
		for(int i = 0; i < dispLocs.size(); i++){
			dispLocs[i] = src.dispLocs[i];
		}
		for(int i = 0; i < frcLocs.size(); i++){
			frcLocs[i] = src.frcLocs[i];
		}
	};

	void addDeflections(Matrix deflections);
	void resolveForces(Matrix nForces) {forces = nForces;};

	Matrix getDisplacements() {return displacements;};
	Matrix getForces() {return forces;};

	std::vector<int> getDispLocs() {return dispLocs;};

	Matrix displacements_reduced();
	Matrix forces_reduced();

private:
	int dim;

	std::vector<int> dispLocs;
	std::vector<int> frcLocs;

	Matrix displacements;
	Matrix forces;

	void initMats(std::vector<double> disps, std::vector<double> frcs);
};

#endif