#pragma once

#include <string>
#include "cEdge.hpp"
#include "cNode.hpp"
#include "cSmartArray.hpp"
#include "cPointXYZ.hpp"
#include "cRoad.hpp"

class cCity 
{
public:
	unsigned int nodeID; 
	std::string name;
	cPointXYZ locationXYZ;	
	cSmartArray<cRoad> vecRoads; 
	bool bVisited = false;

};


