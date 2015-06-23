#ifndef MEMBER_H
#define MEMBER_H

#include <math.h>
#include <vector>
#include "Node.h"
#include "Material.h"

class Member
{
public:
	//CONSTRUCTOR
	Member(std::vector<Node> _nodes, Material material, int numNodes):
		nodes(2), cctMat(16), stfMat(16) {initMember(_nodes, material, numNodes);};
	Member(const Member& src):
		mod(mod), area(area), len(len), dir(dir), nodes(src.nodes.size()), cctMat(src.cctMat.size()), stfMat(src.stfMat.size())
	{
		for(int i = 0; i < 16; i++){
			cctMat[i] = src.cctMat[i];
			stfMat[i] = src.stfMat[i];
			switch(i){
				case 0:
				case 1:
					nodes[i] = src.nodes[i];
				default:
					;
			}
		}
	};

	//ACCESS METHODS
	std::vector<int> getCctMat() {return cctMat;};
	std::vector<double> getLSM() {return stfMat;};


private:
	//FIELDS:
	long long mod;
	double area;
	double len;
	double dir;

	std::vector<Node> nodes;
	std::vector<int> cctMat;
	std::vector<double> stfMat;

	//HEPER METHODS
	void initMember(std::vector<Node> _nodes, Material material, int numNodes);

	void calcLen();
	void calcDir();
	void calcCctMat(int numNodes);
	void calcStfMat();

	int CMH(int n);
	double SMH(int n);
	double deltaX();
	double deltaY();
};

#endif