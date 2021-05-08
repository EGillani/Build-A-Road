/*
* Course: INFO3135 - Project 2
* Project: Cities Connected by Roads
* Author: Eraj Gillani (0858887)
* DATE: December 10th 2020
*/

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "cSmartArray.hpp"
#include "cEdge.hpp"
#include "cNode.hpp"
#include "cCity.hpp"
#include "ReadGenFiles.hpp"
#include "terrainCalc.hpp"


int main()
{
	//READ FIRST: change studentnumber to yours and make sure the file is sitting in the project folder 
	std::string studentNumber = "0858887";

	std::string OriginalTerrianToInput = "TerrainDataInput" + studentNumber + ".txt";
	//Declare vectors
	cSmartArray<cNode> vecNodes;
	cSmartArray<cEdge> vecEdges;
	cSmartArray<cCity> vecCities;

	//Read in File 
	bool readInWorked = readInTerrainFile(OriginalTerrianToInput, vecNodes, vecEdges, vecCities);

	//create an instance of the class that holds all the calculation methods 
	terrianCalc tc;

	/*Q3 print out cities***************************************************************/
	tc.printCities(vecCities);

	//Print out file for Q4
	bool outputWorkedQ4 = outputTerrainFile(studentNumber, "4", vecNodes, vecEdges, vecCities);
	if (outputWorkedQ4 == true)
	{
		std::cout << "Q4 File ready" << std::endl;
	}

	/*Q5***************************************************************/
	cCity closest = tc.findClosestCityToOrigin(vecCities);
	cCity farthest = tc.findFurthestCityToOrigin(vecCities);
	std::cout << "\nClosest to Origin:" << closest.name << std::endl;
	std::cout << "Furthest from Origin:" << farthest.name << std::endl;

	/*Q6***************************************************************/
	std::cout << "Making a road from the closest city from origin to the farthest city from origin..." << std::endl;
	int totalCost = tc.makeARoad(closest.nodeID, farthest.nodeID, vecNodes, vecEdges, vecCities);
	std::cout << "Road made and the cost from closest to farthest city is " << totalCost << std::endl;

	//Print out file for Q6
	bool outputWorkedQ6 = outputTerrainFile(studentNumber, "6", vecNodes, vecEdges, vecCities);
	if (outputWorkedQ6 == true)
	{
		std::cout << "Q6 File ready" << std::endl;
	}

	/*Q7***************************************************************/
	std::cout << "\nBuilding the rest of the Roads now..." << std::endl;
	//Step 1: Feeney notes - you want to connect the 2 cities from Q5 to their nearest neighbours 
	//the function findClosestCityWNoRoads will make sure it picks a city that doesn't have a road 
	cCity chosenCity = tc.findCity(vecCities, closest.nodeID);//change the 2nd argument to the city you want 
	cCity closestCityToChosenCity = tc.findClosestCityWNoRoads(chosenCity.nodeID, vecCities);
	totalCost = tc.makeARoad(chosenCity.nodeID, closestCityToChosenCity.nodeID, vecNodes, vecEdges, vecCities);

	closestCityToChosenCity = tc.findClosestCityWNoRoads(chosenCity.nodeID, vecCities);
	totalCost = tc.makeARoad(chosenCity.nodeID, closestCityToChosenCity.nodeID, vecNodes, vecEdges, vecCities);
	//find the two cities closet to the farthest city from origin and make roads
	chosenCity = tc.findCity(vecCities, farthest.nodeID);//change the 2nd argument to the city you want 
	closestCityToChosenCity = tc.findClosestCityWNoRoads(chosenCity.nodeID, vecCities);
	totalCost = tc.makeARoad(chosenCity.nodeID, closestCityToChosenCity.nodeID, vecNodes, vecEdges, vecCities);
	closestCityToChosenCity = tc.findClosestCityWNoRoads(chosenCity.nodeID, vecCities);
	totalCost = tc.makeARoad(chosenCity.nodeID, closestCityToChosenCity.nodeID, vecNodes, vecEdges, vecCities);

	//Step 2: Feeney notes - repeat this process with the four remaining cities that don't yet thave roads 
	for (unsigned int i = 0; i < vecCities.size(); i++)
	{
		if (vecCities[i].vecRoads.size() == 0)
		{
			cCity chosenCity = tc.findCity(vecCities, vecCities[i].nodeID);//change the 2nd argument to the city you want 
			cCity closestCityToChosenCity = tc.findClosestCityWNoRoads(chosenCity.nodeID, vecCities);
			totalCost = tc.makeARoad(chosenCity.nodeID, closestCityToChosenCity.nodeID, vecNodes, vecEdges, vecCities);
			closestCityToChosenCity = tc.findClosestCityWNoRoads(chosenCity.nodeID, vecCities);
			totalCost = tc.makeARoad(chosenCity.nodeID, closestCityToChosenCity.nodeID, vecNodes, vecEdges, vecCities);

		}
	}

	//Step 3: Feeney notes - if there are any cities that only have one (1) road than traverse 
	for (unsigned int i = 0; i < vecCities.size(); i++)
	{
		if (vecCities[i].vecRoads.size() == 1)
		{
			cCity chosenCity = tc.findCity(vecCities, vecCities[i].nodeID);//change the 2nd argument to the city you want 
			cCity closestCityToChosenCity = tc.findClosestCityWNoRoads(chosenCity.nodeID, vecCities);
			totalCost = tc.makeARoad(chosenCity.nodeID, closestCityToChosenCity.nodeID, vecNodes, vecEdges, vecCities);

		}
	}
	std::cout << "All Roads were built!" << std::endl;

	////set starting city (closest to origin) as startpoint 
	std::cout << "\nTraverse through the Cities to see if they are all connected:" << std::endl;
	unsigned int startingNode = closest.nodeID;

	//all vecCities[index].bisVisited all are initialized to false; 
	tc.depthFirstSearchTraversal(startingNode, vecCities);
	for (unsigned int i = 0; i < vecCities.size(); i++)
	{
		if (vecCities[i].bVisited == true)
		{
			std::cout << "["<< i+1 << "] :" << vecCities[i].name << " was visited" << std::endl;
		}
		else
		{
			std::cout << "[" << i+1 << "] :" << vecCities[i].name << " was not visited" << std::endl;
		}

	}

	bool outputWorkedQ7 = outputTerrainFile(studentNumber, "7", vecNodes, vecEdges, vecCities);
	if (outputWorkedQ7 == true)
	{
		std::cout << "\nQ7 File ready" << std::endl;
	}

	return 0;
}
