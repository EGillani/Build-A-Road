#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "cSmartArray.hpp"
#include "cCity.hpp"

//Reads in the file to fill Vectors 
bool readInTerrainFile(std::string fileName, cSmartArray<cNode>& vecNodes, cSmartArray<cEdge>& vecEdges, cSmartArray<cCity>& vecCities)
{
	//std::string fileName = "TerrainDataInput" + studentNumber + ".txt";
	std::ifstream theFile(fileName);
	if (!theFile.is_open())
	{
		std::cout << "ERROR: Can't open file" << std::endl;
		return false;
	}

	unsigned int numberOfNodes = 0;
	unsigned int numberOfEdges = 0;
	unsigned int numberOfCities = 0;

	// Start reading the file 
	theFile >> numberOfNodes;
	theFile >> numberOfEdges;
	theFile >> numberOfCities;
	//std::cout << "Nodes = " << numberOfNodes << std::endl;
	//std::cout << "Edges = " << numberOfEdges << std::endl;
	//std::cout << "Cities = " << numberOfCities << std::endl;

	// Load all the nodes
	for (unsigned int count = 0; count != numberOfNodes; count++)
	{
		cNode tempNode;
		// o	X location (float)
		// o	Y location (float)
		// o	Height or Z (float)
		// o	Is there a city here, which is either a “0” (false) or “1” (true)
		// o	The name of the city (which is one word, no spaces), or the letter “x”
		theFile >> tempNode.locationXYZ.x;
		theFile >> tempNode.locationXYZ.y;
		theFile >> tempNode.locationXYZ.z;
		int intIsCity = 0;
		theFile >> intIsCity;		// 0 or 1

		tempNode.bIsCity = (intIsCity == 0 ? false : true);

		theFile >> tempNode.cityName;		// "x" or the city name


		if (tempNode.bIsCity)
		{
			cCity tempCity;
			tempCity.nodeID = count; 
			tempCity.name = tempNode.cityName;
			tempCity.bVisited = false;
			tempCity.locationXYZ.x = tempNode.locationXYZ.x;
			tempCity.locationXYZ.y = tempNode.locationXYZ.y;
			tempCity.locationXYZ.z = tempNode.locationXYZ.z;

			vecCities.push_back(tempCity);
			//std::cout << "Found " << tempNode.cityName << std::endl;
		}


		vecNodes.push_back(tempNode);
	}
	//	std::cout << "Read " << vecNodes.size() << " nodes" << std::endl;

		// Load all the edges
	for (unsigned int count = 0; count != numberOfEdges; count++)
	{
		cEdge tempEdge;
		// o	Start vertex / node ID, which is an unsigned integer.
		// o	End vertex / node ID, which is an unsigned integer.
		// o	“Cost” to go from one node / vertex to the other, an signed integer.
		// o	Is a road, which is “0” (false) or “1” (true)

		theFile >> tempEdge.startNodeID;
		theFile >> tempEdge.endNodeID;
		theFile >> tempEdge.cost;

		int intIsRoad = 0;
		theFile >> intIsRoad;		// 0 or 1
		tempEdge.isRoad = (intIsRoad == 0 ? false : true);

		vecEdges.push_back(tempEdge);
	}
	//std::cout << "Read " << vecEdges.size() << " edges" << std::endl;
	theFile.close();

	return true;
}

bool outputTerrainFile(std::string StudentNumber, std::string questionNumber, cSmartArray<cNode> & vecNodes, cSmartArray<cEdge> & vecEdges, cSmartArray<cCity>  & vecCities)
{
	//PRINT OUT THE FILE 
	std::string fileName = "TerrainDataInput" + StudentNumber + "_Q" + questionNumber + ".txt";

	std::stringstream ssFileName;
	ssFileName << fileName;

	fileName = ssFileName.str();

	std::ofstream theNewFile(fileName.c_str());
	if (!theNewFile.is_open())
	{
		std::cout << "Error: Can't open " + fileName + " for output." << std::endl;
		return false;
	}
	theNewFile << vecNodes.size() << std::endl;
	theNewFile << vecEdges.size() << std::endl;
	theNewFile << vecCities.size() << std::endl;

	for (unsigned int i = 0; i < vecNodes.size(); i++)
	{
		cNode tempNode = vecNodes[i];

		theNewFile
			<< tempNode.locationXYZ.x << " "
			<< tempNode.locationXYZ.y << " "
			<< tempNode.locationXYZ.z << " ";

		theNewFile << (tempNode.bIsCity ? 1 : 0) << " ";

		theNewFile << (tempNode.bIsCity ? tempNode.cityName : "x");

		theNewFile << std::endl;

	}

	for (unsigned int i = 0; i < vecEdges.size(); i++)
	{
		cEdge tempEdge = vecEdges[i];

		theNewFile
			<< tempEdge.startNodeID << " "
			<< tempEdge.endNodeID << " ";

		theNewFile << tempEdge.cost << " ";

		if (tempEdge.isRoad)
		{
			theNewFile << 1 << " ";
		}
		else
		{
			theNewFile << 0 << " ";
		}

		theNewFile << std::endl;
	}

	theNewFile.close();
	return true; 
}