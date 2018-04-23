#pragma once
#include "PlaneObj.h"
#define MAX_SCORE 999
class Target :
	public PlaneObj
{
public:

	Target(Vec3<float> pos, Texture2D texture, int& scoreRef, int scoreInc = 1);
	virtual ~Target();

	virtual bool OnCollide(std::string tag);

private:
	//How much hitting this target should incremenet the score reference by
	int scoreInc;
	int& scoreRef;
};

