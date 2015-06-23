#include "Member.h"

//HELPER METHODS
//Initialization helpers
void Member::initMember(std::vector<Node> _nodes, Material material, int numNodes)
{
	nodes[0] = _nodes[0];
	nodes[1] = _nodes[1];
	mod = material.modulus;
	area = material.area;

	calcLen();
	calcDir();
	calcCctMat(numNodes);
	calcStfMat();
}

void Member::calcLen()
{
	len = sqrt(pow(deltaX(), 2) + pow(deltaY(), 2));
}

void Member::calcDir()
{
	dir = atan(deltaY() / deltaX());
}

//Initializes the member's connectivity to the global stiffness
//matrix.
void Member::calcCctMat(int numNodes)
{
	for(int i = 0; i < 16; i++)
	{
		cctMat[i] = CMH(i / 4) * numNodes * 2 + CMH(i % 4);
	}
}

//Initializes the member's local stiffness values.
void Member::calcStfMat()
{
	double stf = mod * area / len;
	for(int i = 0; i < 16; i++)
	{
		stfMat[i] = SMH(i % 4) * SMH(i / 4) * stf;
	}
}


//Other helpers:
//Connectivity matrix helper assists in calculating the local
//stiffness matrix's corresponding global stiffness coordinates
int Member::CMH(int n)
{
	switch(n)
	{
	case 0:
		return (nodes[0].globalN -1 ) * 2;
	case 1:
		return (nodes[0].globalN - 1) * 2 + 1;
	case 2:
		return (nodes[1].globalN - 1) * 2;
	case 3:
		return (nodes[1].globalN -1 ) * 2 + 1;
	default:
		return -1;
	}
}

//Stiffness matrix helper assists in the calculation of the local
//stiffness matrix's elements
double Member::SMH(int n)
{
	switch(n)
	{
	case 0:
		return cos(dir);
	case 1:
		return sin(dir);
	case 2:
		return -cos(dir);
	case 3:
		return -sin(dir);
	default:
		return 2;
	}
}

//Calculates member's length in the global x direction
double Member::deltaX()
{
	return(nodes[1].coords[0] - nodes[0].coords[0]);
}

//Calculates member's length in the global y direction
double Member::deltaY()
{
	return(nodes[1].coords[1] - nodes[0].coords[1]);
}