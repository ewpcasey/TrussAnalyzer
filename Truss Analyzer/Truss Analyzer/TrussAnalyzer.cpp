#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "MemberManager.h"
#include "MatrixManager.h"
#include "ConstraintManager.h"

using namespace std;

struct TrussData
{
	TrussData(NodeManager nodeManager, MemberManager memManager, ConstraintManager cstManager):
		nodeManager(nodeManager), memManager(memManager), cstManager(cstManager) {};
	NodeManager nodeManager;
	MemberManager memManager;
	ConstraintManager cstManager;
};

TrussData initPrompt();
TrussData initTestParams();
void analyze(TrussData trussData);

int main(int argc, TCHAR *argv[])
{
	HWND console = GetConsoleWindow();

	analyze(initPrompt());

	char a;
	cin >> a;

	return 0;
}

TrussData initPrompt()
{
	int numNodes;
	int numMems;
	int numDCs;
	int temp;

	//Prompt user for number of nodes.
	//Init crdMat and cstMat vectors.
	cout << "Input number of nodes: ";
	cin >> numNodes;
	vector<double> crdMat(numNodes * 2);

	//Prompt user for node coordinates
	cout << "\nNode Coordinates:";
	for(int i = 0; i < numNodes; i++)
	{
		cout << "\nNode " << i + 1 << ":\n";

		cout << "X: ";
		cin >> crdMat[2 * i];

		cout << "Y: ";
		cin >> crdMat[2 * i + 1];
	}

	//Prompt user for degree-of-freedom conditions:
	cout << "\nNode constraints:";
	cout << "\nNumber of displacement constraints: ";
	cin >> numDCs;
	vector<int> dspLocs(numDCs);
	vector<int> frcLocs(numNodes * 2 - numDCs);
	vector<double> displacements(numDCs);
	vector<double> forces(numNodes * 2 - numDCs);

	cout << "\nDisplacements:";
	for(int i = 0; i < numDCs; i++)
	{
		cout << "\nDOF: ";
		cin >> temp;
		dspLocs[i] = --temp; 
		cout << "Magnitude: ";
		cin >> displacements[i];
	}

	cout << "\nForces:";
	for(int i = 0; i < 2 * numNodes - numDCs; i++)
	{
		cout << "\nDOF: ";
		cin >> temp;
		frcLocs[i] = --temp; 
		cout << "Magnitude: ";
		cin >> forces[i];
	}

	//Prompt user for number of members:
	cout << "\n\nInput number of members: ";
	cin >> numMems;
	vector<int> cctMat(numMems * 2);

	//Prompt user for member connections:
	for(int i = 0; i < numMems; i++)
	{
		cout << "\nConnecting nodes of member "<< (i+1) << ":\n";

		cout << "Node 1: ";
		cin >> cctMat[2 * i];

		cout << "Node 2: ";
		cin	>> cctMat[2 * i + 1];
	}

	//Prompt user for material types
	//Initialize material set
	cout << "\nInput number of materials used: ";
	cin >> temp;
	vector<Material> matSet(temp);
	for(int i = 0; i < temp; i++)
	{
		matSet[i] = Material();

		cout << "\nMaterial " << i + 1 << ": ";
		cout << "\nModulus: ";
		cin >> matSet[i].modulus;
		cout << "Area: ";
		cin >> matSet[i].area;
	}

	//Prompt user for material matrix
	vector<int> matMat(numMems);
	cout << "\nInput material used for each member:\n";
	for(int i = 0; i < numMems; i++)
	{
		cout << "Member " << i + 1 << ": ";
		cin >> matMat[i];
	}

	NodeManager nodeManager(crdMat, numNodes);
	MemberManager memManager(nodeManager, cctMat, matSet, matMat);
	ConstraintManager cstManager(numNodes * 2, dspLocs, frcLocs, displacements, forces);

	return TrussData(nodeManager, memManager, cstManager);
}

TrussData initTestParams()
{
	double crds[8] = {0,0,1,0,0,1,1,1};
	std::vector<double> crdMat(crds, crds + 8);

	double disps[4] = {0, 0, 0, 0};
	double frcs[4] = {0, -10000, 0, -10000};
	std::vector<double> displacements(disps, disps + 4);
	std::vector<double> forces(frcs, frcs + 4);

	int dspLocs[4] = {0, 1, 2, 3};
	int frcLocs[4] = {4, 5, 6, 7};
	std::vector<int> dispLocs(dspLocs, dspLocs + 4);
	std::vector<int> forceLocs(frcLocs, frcLocs + 4);

	int ccts[10] = {1,2,1,3,2,3,2,4,3,4};
	std::vector<int> cctMat(ccts, ccts + 10);

	std::vector<Material> matSet(1);
	matSet[0].area = .1;
	matSet[0].modulus = 200;

	int mats[5] = {1,1,1,1,1};
	std::vector<int> matMat(mats, mats + sizeof mats / sizeof mats[0]);

	NodeManager nodeManager(crdMat, 4);
	MemberManager memManager(nodeManager, cctMat, matSet, matMat);
	ConstraintManager cstManager(8, dispLocs, forceLocs, displacements, forces);

	return TrussData(nodeManager, memManager, cstManager); 
}

void analyze(TrussData trussData)
{
	Matrix GSM = Matrix(trussData.memManager.getGSM(), trussData.nodeManager.getNumNodes() * 2, trussData.nodeManager.getNumNodes() * 2);
	Matrix red_inv_GSM = MatrixManager::invert(MatrixManager::eliminate(GSM, trussData.cstManager.getDispLocs(), trussData.cstManager.getDispLocs()));
	trussData.cstManager.addDeflections(MatrixManager::multMatrices(red_inv_GSM, trussData.cstManager.forces_reduced()));
	trussData.cstManager.resolveForces(MatrixManager::multMatrices(GSM, trussData.cstManager.getDisplacements()));

	cout << "Stiffness Matrix:\n";
	MatrixManager::print(GSM);
	cout << "Displacements:\n";
	MatrixManager::print(trussData.cstManager.getDisplacements());
	cout << "Forces:\n";
	MatrixManager::print(trussData.cstManager.getForces());
}