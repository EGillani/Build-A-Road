#pragma once

//	39258 39259 -21 0
// o	Start vertex / node ID, which is an unsigned integer.
// o	End vertex / node ID, which is an unsigned integer.
// o	“Cost” to go from one node / vertex to the other, an signed integer.
// o	Is a road, which is “0” (false) or “1” (true)
class cEdge
{
public:
	unsigned int startNodeID;
	unsigned int endNodeID;
	int cost;
	bool isRoad;

};
