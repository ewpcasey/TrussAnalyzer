#include "MemberManager.h"

//Initializes member set using nodemanager, connectivity matrix and material set.
void MemberManager::initMemSet(const NodeManager& nodeManager, std::vector<int> cctMat, std::vector<Material> matSet, std::vector<int> matMat, int n)
{
	int index;
	for(int i = 0; i < n; i++)
	{
		index = 2 * i;
		Member newMem(nodeManager.getNodePair(cctMat[index], cctMat[index + 1]), matSet[matMat[i] - 1], nodeManager.getNumNodes());
		memSet.push_back(newMem);
	}
}

void MemberManager::assembleGSM()
{
	//Add stiffness elements of each member to appropriate gobal stiffness location
	int size = memSet.size();
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			gsm[getGlobalCrd(i, j)] += getLocStiff(i, j);
		}
	}
}

//helper methods
int MemberManager::getGlobalCrd(int i, int j)
{
	return(memSet[i].getCctMat()[j]);
}

double MemberManager::getLocStiff(int i, int j)
{
	return(memSet[i].getLSM()[j]);
}