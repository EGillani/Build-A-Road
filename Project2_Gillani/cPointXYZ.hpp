#pragma once 

class cPointXYZ
{
public:
	float x, y, z;
    cPointXYZ() = default; 
    cPointXYZ(float x, float y, float z) { 
        this->x = x;
        this->y = y;
        this->z = z;
    }
};