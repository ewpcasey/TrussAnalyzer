#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include <vector>
#include "Member.h"
#include "NodeManager.h"

class MemberManager
{
public:
	//CONSTRUCTOR
	//standard constructor
	MemberManager(const NodeManager& nodeManager, std::vector<int> cctMat, std::vector<Material> matSet, std::vector<int> matMat):
		gsm(pow(2 * nodeManager.getNumNodes(), 2), 0)
		{
			initMemSet(nodeManager, cctMat, matSet, matMat, matMat.size());
			assembleGSM();
		};
	//copy constructor
	MemberManager(const MemberManager& src):
		gsm(src.gsm.size())
	{
		for(int i = 0; i < src.memSet.size(); i++){
			memSet.push_back(src.memSet[i]);
		}
		for(int i = 0; i < gsm.size(); i++){
			gsm[i] = src.gsm[i];
		}
	};

	//gsm access
	std::vector<double> getGSM(){return gsm;};

private:
	std::vector<Member> memSet;
	std::vector<double> gsm;

	void initMemSet(const NodeManager& nodeManager, std::vector<int> cctMat, std::vector<Material> matSet, std::vector<int> matMat, int n);
	void assembleGSM();

	//helpers
	int getGlobalCrd(int i, int j);
	double getLocStiff(int i, int j);
};

#endif