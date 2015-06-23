#include "NodeManager.h"

//ACCESS METHODS
//Returns a vector containing requested nodes. Used in conjunction
//with the connectivity matrix to initialize truss members.
std::vector<Node> NodeManager::getNodePair(int i1, int i2) const
{
	std::vector<Node> toReturn(2);
	toReturn[0] = nodeSet[i1 - 1];
	toReturn[1] = nodeSet[i2 - 1];
	return toReturn;
}


//HELPER METHODS
void NodeManager::initNodeManager(std::vector<double> crdMat, int n)
{
	for(int i = 0; i < n; i++)
	{
		nodeSet[i] = Node();
		nodeSet[i].globalN = i + 1;
		initNCrd(nodeSet[i], crdMat, i);
	}
}

//Initializes node coordinates.
void NodeManager::initNCrd(Node& node, std::vector<double> crdMat, int i)
{
	int index = i * 2;
	node.coords[0] = crdMat[index];
	node.coords[1] = crdMat[index + 1];
}

