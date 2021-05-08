#pragma once
#include <string>
#include "cPointXYZ.hpp"

//0 0 29.0716 0 x
// o	X location (float)
// o	Y location (float)
// o	Height or Z (float)
// o	Is there a city here, which is either a “0” (false) or “1” (true)
// o	The name of the city (which is one word, no spaces), or the letter “x”
class cNode
{
public:
	cPointXYZ locationXYZ;
	bool bIsCity;	
	std::string cityName;
};

