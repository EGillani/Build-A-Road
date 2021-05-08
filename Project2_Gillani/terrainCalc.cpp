#include "terrainCalc.hpp"

void  terrianCalc::printCities(cSmartArray<cCity>& vecCities)
{
	for (unsigned int i = 0; i < vecCities.size(); i++)
	{
		std::cout << "City:" << vecCities[i].name << "(nodeid:" << vecCities[i].nodeID << ")" << std::endl;
		std::cout << "\tLocation:" << vecCities[i].locationXYZ.x << ",";
		std::cout << vecCities[i].locationXYZ.y << ",";
		std::cout << vecCities[i].locationXYZ.z << std::endl;

	}
}


float terrianCalc::getDistance(cPointXYZ a, cPointXYZ b)
{

	double deltaX = (double)a.x - (double)b.x;
	double deltaY = (double)a.y - (double)b.y;
	double deltaZ = (double)a.z - (double)b.z;
	return (float)sqrt((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));
}

// A = city A
// B = city B
// thisPointXYZ = origin
//takes two points and compares the closest
cNode  terrianCalc::whichNodeIsCloserToHere(cNode A, cNode B, cPointXYZ thisPoint)
{
	float distanceA = getDistance(A.locationXYZ, thisPoint);
	float distanceB = getDistance(B.locationXYZ, thisPoint);
	// Test the distance to the city from the origin
	/*if (getDistance(A.locationXYZ, thisPoint) < getDistance(B.locationXYZ, thisPoint))*/
	if (distanceA < distanceB)
	{
		return A;
	}
	else
	{
		return B;
	}
}

cNode terrianCalc::whichNodeIsFartherToHere(cNode A, cNode B, cPointXYZ thisPoint)
{
	float distanceA = getDistance(A.locationXYZ, thisPoint);
	float distanceB = getDistance(B.locationXYZ, thisPoint);
	// Test the distance to the city from the origin
	/*if (getDistance(A.locationXYZ, thisPoint) < getDistance(B.locationXYZ, thisPoint))*/
	if (distanceA > distanceB)
	{
		return A;
	}
	else
	{
		return B;
	}
}

cCity terrianCalc::findFurthestCityToOrigin(cSmartArray<cCity>& vecCities)
{

	cPointXYZ origin(0, 0, 0);
	cCity furthestCity = vecCities[0];//can change this to test it 
	cNode tempNode;
	cNode cityANode;
	cNode cityBNode;
	bool isCityb = false;
	for (unsigned int i = 0; i < vecCities.size() - 1; i++)
	{
		//populate the nodes
		cityANode.cityName = vecCities[i].name;
		cityANode.locationXYZ = vecCities[i].locationXYZ;
		cityBNode.cityName = vecCities[i + 1].name;
		cityBNode.locationXYZ = vecCities[i + 1].locationXYZ;
		// Compare with distance, then return the "closest"
		tempNode = whichNodeIsFartherToHere(cityANode, cityBNode, origin);
		if (tempNode.cityName == vecCities[i + 1].name)
		{
			isCityb = true;
		}
		// See if the city is "the closest so far"
		if (getDistance(tempNode.locationXYZ, origin) > getDistance(furthestCity.locationXYZ, origin))
		{
			//do this if the second city was the result 
			if (isCityb == false)
			{
				furthestCity = vecCities[i];
			}
			else
			{
				furthestCity = vecCities[i + 1];
			}
		}
	}
	return furthestCity;
}

cCity terrianCalc::findClosestCityToOrigin(cSmartArray<cCity>& vecCities)
{
	cPointXYZ origin(0, 0, 0);
	cCity closestCity = vecCities[5];//can change this to test it 
	cNode tempNode;
	cNode cityANode;
	cNode cityBNode;
	bool isCityb = false;
	for (unsigned int i = 0; i < vecCities.size() - 1; i++)
	{
		cityANode.cityName = vecCities[i].name;
		cityANode.locationXYZ = vecCities[i].locationXYZ;
		cityBNode.cityName = vecCities[i + 1].name;
		cityBNode.locationXYZ = vecCities[i + 1].locationXYZ;
		// Compare with distance, then return the "closest"
		tempNode = whichNodeIsCloserToHere(cityANode, cityBNode, origin);
		if (tempNode.cityName == vecCities[i + 1].name)
		{
			isCityb = true;
		}
		// See if the city is "the closest so far"
		if (getDistance(tempNode.locationXYZ, origin) < getDistance(closestCity.locationXYZ, origin))
		{
			if (isCityb == false)
			{
				closestCity = vecCities[i];
			}
			else
			{
				closestCity = vecCities[i + 1];
			}
		}
	}

	return closestCity;
}

// Return the node index of the city...
// Returns the node indes of the city
// If it can't find any, returns INT_MAX
unsigned int  terrianCalc::findNextCity(cSmartArray<cNode>& vecNodes, unsigned int startNode)
{
	for (unsigned int index = startNode; index != vecNodes.size(); index++)
	{
		// Is this a city?
		if (vecNodes[index].bIsCity)
		{
			// Yup, it is
			return index;
		}
	}

	return INT_MAX;
}

//Q6 - Step 0: finding associated edges (1:30:00~) 
bool  terrianCalc::findAssociatedEdges(unsigned int nodeIDtoFind, cSmartArray<cEdge>& vecAllEdges,	/* ALL Edges */ cSmartArray<cEdge>& vecFoundEdges)		/* Adjacent 'returned' */
{
	vecFoundEdges.clear();

	for (unsigned int index = 0; index != vecAllEdges.size(); index++)
	{
		// If either of the node IDs in the edge match, then it's associate with this node (remember this is an undirected graph)
		if ((vecAllEdges[index].startNodeID == nodeIDtoFind) || (vecAllEdges[index].endNodeID == nodeIDtoFind))
		{
			// Add it to the "list" of adjacent edges
			vecFoundEdges.push_back(vecAllEdges[index]);
		}
	}

	return true;
}

//Q6 - REVISED (1:38:00) - we want to return all the other nodes 
// Assumes the edge list has only associated nodes
bool  terrianCalc::FindAssociatedNodesByEdgeList(unsigned int nodeIDtoFind,cSmartArray<cEdge>& vecFoundEdges, cSmartArray<cEdge>& vecAdjacentNodesEdges) //produce another list? found associated nodes? 
{
	vecAdjacentNodesEdges.clear();

	for (unsigned int index = 0; index != vecFoundEdges.size(); index++)
	{
		// If the startID matches nodeIDtoFind, return the endID
		if (vecFoundEdges[index].startNodeID == nodeIDtoFind)
		{
			// Add it to the "list" of adjacent nodes that are going AWAY from the node (they will be the endnodeID!) 
			vecAdjacentNodesEdges.push_back(vecFoundEdges[index]);
		}
		// otherwise, return the startID
	}
	return true; 

}

//Q6 - Step 0: finding adjacent nodes (1:24:00~)  OLD ONE but still gives picture 
// Find nodes adjacent (connected to) "this" node
 //Returns false if it can't find the node matching nodeID
bool  terrianCalc::findAdjacentNodes(cSmartArray<cEdge>& vecAdjacentNodesEdges, cSmartArray<cNode>& vecNodes, cSmartArray<cNode>& vecAdjacentNodes)	/* Adjacent 'returned' */
{
	vecAdjacentNodes.clear();

	for ( unsigned int index = 0; index != vecAdjacentNodesEdges.size(); index++ )
	{
		//find the nodes! 
		for (unsigned int n = 0; n != vecNodes.size(); n++)
		{
			//endNodeID is the node attached to the startNodeID(the node we are trying to move AWAY from) 
			if (vecAdjacentNodesEdges[index].endNodeID == n)
			{
				//populate the adjacent node list with the node we want 
				vecAdjacentNodes.push_back(vecNodes[n]);
			}
		}

	}
	return true;
}


//Q6 - STEP 2: 1:18:00~ vid
void  terrianCalc::getNodesThatAreCloser(cSmartArray<cEdge>& vecAdjacentNodesEdges,cSmartArray<cNode>& vecAdjacentNodes, cSmartArray<cEdge>& vecCloserNodesEdges, cPointXYZ referencePoint, cPointXYZ destinationPoint)
{
	//FEENEYS NOTES:
	// If node is FARTHER than the referencePoint point, then discard.
	//in the end vecTestNodes will be nodes that are closer 
	//before calculating cost-value 

	//Warning: pararell arrays concept going on here with vecAdjacentNodes and vecAdjacentNodesEdges 

	cNode tempNode;//Getdistance(startinCity, endingCity) 
	float currentTotalDistance = getDistance(referencePoint, destinationPoint);
	for (unsigned int i = 0; i < vecAdjacentNodes.size(); i++)
	{ 
		if (getDistance(vecAdjacentNodes[i].locationXYZ, destinationPoint) < currentTotalDistance)
		{
			vecCloserNodesEdges.push_back(vecAdjacentNodesEdges[i]);
		}
	}
}

//Q6 - STEP 3: another function that finds the cheapest edge  
cEdge terrianCalc::findCheapestEdge(cSmartArray<cEdge>& vecCloserNodesEdges, cSmartArray<cEdge>& vecEdges)
{
	cEdge cheapestEdge = vecCloserNodesEdges[0];
	for (unsigned int i = 0; i < vecCloserNodesEdges.size(); i++)
	{
		if (vecCloserNodesEdges[i].cost < cheapestEdge.cost)
		{
			cheapestEdge = vecCloserNodesEdges[i];
		}
	}
	return cheapestEdge;
}

bool operator == (cEdge const& lhs, cEdge const& rhs) {
	if( (lhs.startNodeID == rhs.startNodeID) && (lhs.endNodeID == rhs.endNodeID))
	{
		return true;
	}
	return false;
}
//Q6 - Step 4: then set the value 0 to one in the text file. 
void terrianCalc::makeAEdgeARoad(cEdge cheapestEdge, cSmartArray<cEdge> vecEdges)
{
	for (unsigned int i = 0; i < vecEdges.size(); i++)
	{
		if (cheapestEdge == vecEdges[i])
		{
			vecEdges[i].isRoad = true; 
		}
	}
}
cCity terrianCalc::findCity(cSmartArray<cCity>& vecCities, unsigned int theCityNodeID)
{
	for (unsigned int i = 0; i < vecCities.size(); i++)
	{
		if (theCityNodeID == vecCities[i].nodeID)
		{
			return vecCities[i];
		}
	}
}

int terrianCalc::makeARoad(unsigned int startingCityNode, unsigned int endingCityNode, cSmartArray<cNode> vecNodes, cSmartArray<cEdge> & vecEdges, cSmartArray<cCity> & vecCities)
{
	unsigned int currentNodeId = startingCityNode;
	int totalCost = 0;
	cPointXYZ destinationPoint = vecNodes[endingCityNode].locationXYZ;

	//got to jump from node to node! While the current node doesn't equate to the node of the node of the destination city 
	while (currentNodeId != endingCityNode)
	{
		cSmartArray<cEdge> vecFoundAssociatedEdges; //need to populate
		findAssociatedEdges(currentNodeId, vecEdges, vecFoundAssociatedEdges);

		cSmartArray<cEdge> vecAdjacentNodesEdges; //nodes associated with those edges as EdgeList! these ones are going AWAY from the node
		FindAssociatedNodesByEdgeList(currentNodeId, vecFoundAssociatedEdges, vecAdjacentNodesEdges);

		cSmartArray<cNode> vecAdjacentNodes; //nodes associated with those edges (Using the edges get the node) 
		findAdjacentNodes(vecAdjacentNodesEdges, vecNodes, vecAdjacentNodes);

		cPointXYZ referencePoint = vecNodes[currentNodeId].locationXYZ;

		cSmartArray<cEdge> vecCloserNodesEdges; //nodes that are moving TOWARDS the city 
		getNodesThatAreCloser(vecAdjacentNodesEdges, vecAdjacentNodes, vecCloserNodesEdges, referencePoint, destinationPoint);

		cEdge cheapestEdge = findCheapestEdge(vecCloserNodesEdges, vecEdges); //get the cheapest edge 
		makeAEdgeARoad(cheapestEdge, vecEdges);

		//add up the costs 
		totalCost += cheapestEdge.cost;

		//set the endNodeID = currentNodeId that will be evaluated. 
		currentNodeId = cheapestEdge.endNodeID;
	}

	//add it the cCity that it now has a road to this other city 
	cCity thestartingCity = findCity(vecCities, startingCityNode);
	//FOR Q7: create a new road that will just hold the nodeID and the name of the city it is connected too
	cRoad theNewRoad;

	//add it to the cityList
	for (unsigned int i = 0; i < vecCities.size(); i++)
	{
		if (startingCityNode == vecCities[i].nodeID)
		{
			theNewRoad.nodeIdForConnectedCity = endingCityNode;
			cCity theEndingCity = findCity(vecCities, endingCityNode);
			theNewRoad.cityName = theEndingCity.name;
			vecCities[i].vecRoads.push_back(theNewRoad);
		}
		else if (endingCityNode == vecCities[i].nodeID)
		{
			cCity theStartingCity = findCity(vecCities, startingCityNode);
			theNewRoad.cityName = theStartingCity.name;
			theNewRoad.nodeIdForConnectedCity = theStartingCity.nodeID;
			vecCities[i].vecRoads.push_back(theNewRoad);
		}
	}
	//std::cout << "A Road has been made" << std::endl;
	return totalCost;
}

cCity terrianCalc::findClosestCityWNoRoads(unsigned int chosenCityNode, cSmartArray<cCity>& vecCities)
{
	cCity chosenCity = findCity(vecCities, chosenCityNode);//change the 2nd argument to the city you want 
	cCity closestCityToChosenCity; //Carlshalton
	//get the largest distance possile between cities in our terrain 
	float closestCityDistance = INT16_MAX;
	float tempClosestCityDistance = 0;
	cPointXYZ startingCityPoint = chosenCity.locationXYZ;
	for (unsigned int i = 0; i < vecCities.size(); i++)
	{
		if (chosenCity.name == vecCities[i].name)
		{
			continue;
		}
		//do a test if that closest city already has a road to this city
		bool foundRoad = false;
		for (unsigned int c = 0; c < vecCities[i].vecRoads.size(); c++)
		{
			if (chosenCity.name == vecCities[i].vecRoads[c].cityName)
			{
				foundRoad = true;
			}
		}
		//than see if it will be the closest city 
		if (foundRoad == false)
		{
			tempClosestCityDistance = getDistance(vecCities[i].locationXYZ, startingCityPoint);
			if (tempClosestCityDistance < closestCityDistance)
			{
				closestCityDistance = tempClosestCityDistance;
				closestCityToChosenCity = vecCities[i];
			}
		}

	}
	return closestCityToChosenCity;
}

unsigned int terrianCalc::findCityIndexInVecCities(cSmartArray<cCity>& vecCities, unsigned int theCityNodeID)
{
	for (unsigned int i = 0; i < vecCities.size(); i++)
	{
		if (theCityNodeID == vecCities[i].nodeID)
		{
			return i;
		}
	}
}

void terrianCalc::depthFirstSearchTraversal(unsigned int atCityNode, cSmartArray<cCity>& vecCities)
{
	unsigned int indexOfDestinationCity = findCityIndexInVecCities(vecCities, atCityNode);

	//if the city has already been visited than set get out of function 
	if (vecCities[indexOfDestinationCity].bVisited == true)
	{
		return;
	}
	else
	{
		//visit it and set it to true
		vecCities[indexOfDestinationCity].bVisited = true;
	}

	cSmartArray<unsigned int> neighbourCities; //tail of 2d list 
	cCity neighbour;
	for (unsigned int i = 0; i < vecCities[indexOfDestinationCity].vecRoads.size(); i++)
	{
		neighbourCities.push_back(vecCities[indexOfDestinationCity].vecRoads[i].nodeIdForConnectedCity);
	}

	for (unsigned int i = 0; i < neighbourCities.size(); i++)
	{
		terrianCalc::depthFirstSearchTraversal(neighbourCities[i], vecCities);
	}

	return;
}