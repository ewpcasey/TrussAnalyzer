#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <vector>
#include "Node.h"

class NodeManager
{
public:
	//CONSTRUCTORS
	NodeManager(std::vector<double> crdMat, int n):
		numNodes(n), nodeSet(n) {initNodeManager(crdMat, n);};
	NodeManager(const NodeManager& src):
		numNodes(src.numNodes), nodeSet(numNodes)
	{
		for(int i = 0; i < numNodes; i++){
			nodeSet[i] = src.nodeSet[i];
		}
	};

	//ACCESS METHODS
	std::vector<Node> getNodePair(int node1, int node2) const;
	int getNumNodes() const {return numNodes;};

private:
	//FIELDS
	int numNodes;
	std::vector<Node> nodeSet;

	//HELPER METHODS
	void initNodeManager(std::vector<double> crdMat, int n);
	void initNCrd(Node& node, std::vector<double> crdMat, int index);
};

#endif