
#pragma once
#include <string>
#include <iostream>
#include "cSmartArray.hpp"
#include "cEdge.hpp"
#include "cCity.hpp"
#include "cNode.hpp"

class terrianCalc
{
public:

	void  printCities(cSmartArray<cCity>& vecCities);

	float getDistance(cPointXYZ a, cPointXYZ b);

	// A = city A
	// B = city B
	// thisPointXYZ = origin
	//takes two points and compares the closest
	cNode whichNodeIsCloserToHere(cNode A, cNode B, cPointXYZ thisPoint);

	cCity findClosestCityToOrigin(cSmartArray<cCity>& vecCities);

	cNode whichNodeIsFartherToHere(cNode A, cNode B, cPointXYZ thisPoint);

	cCity findFurthestCityToOrigin(cSmartArray<cCity>& vecCities);

	// Return the node index of the city...
	// Returns the node indes of the city
	// If it can't find any, returns INT_MAX
	unsigned int findNextCity(cSmartArray<cNode>& vecNodes, unsigned int startNode);

	//Q6 - Step 0: finding associated edges (1:30:00~) 
	bool findAssociatedEdges(unsigned int nodeIDtoFind, cSmartArray<cEdge>& vecAllEdges,	/* ALL Edges */ cSmartArray<cEdge>& vecFoundEdges);		/* Adjacent 'returned' */
	//Q6 - REVISED (1:38:00) - we want to return all the other nodes 
	// Assumes the edge list has only associated nodes
	bool FindAssociatedNodesByEdgeList(unsigned int nodeIDtoFind, cSmartArray<cEdge>& vecFoundEdges, cSmartArray<cEdge>& vecAdjacentNodes);


	//Q6 - Step 0: finding adjacent nodes (1:24:00~)  OLD ONE but still gives picture 
	// Find nodes adjacent (connected to) "this" node
	 //Returns false if it can't find the node matching nodeID
	bool findAdjacentNodes(cSmartArray<cEdge>& vecAdjacentNodesEdges, cSmartArray<cNode>& vecNodes, cSmartArray<cNode>& vecAdjacentNodes);

	//Q6 - STEP 2: 1:18:00~ vid (eliminate nodes that are farther away from the destination city) 
	void getNodesThatAreCloser(cSmartArray<cEdge>& vecAdjacentNodesEdges, cSmartArray<cNode>& vecAdjacentNodes, cSmartArray<cEdge>& vecCloserNodesEdges,cPointXYZ referencePoint, cPointXYZ destinationPoint);

	////Q6 - STEP 3: another function that finds the cheapest edge  
	cEdge findCheapestEdge(cSmartArray<cEdge>& vecCloserNodesEdges, cSmartArray<cEdge>& vecEdges);

	//Q6 - STEP 4: make that edge a road! 
	void makeAEdgeARoad(cEdge cheapestEdge, cSmartArray<cEdge> vecEdges);

	int makeARoad(unsigned int startingCityNode, unsigned int endingCityNode, cSmartArray<cNode> vecNodes, cSmartArray<cEdge> & vecEdges, cSmartArray<cCity> & vecCities);

	//Q7 functions 
	cCity findCity(cSmartArray<cCity>& vecCities, unsigned int theCityNodeID);

	cCity findClosestCityWNoRoads(unsigned int startingCityNode, cSmartArray<cCity>& vecCities);
	
	unsigned int findCityIndexInVecCities(cSmartArray<cCity>& vecCities, unsigned int theCityNodeID);

	void depthFirstSearchTraversal(unsigned int atCityNode, cSmartArray<cCity>& vecCities);

};
