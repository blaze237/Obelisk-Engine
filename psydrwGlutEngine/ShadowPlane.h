#pragma once
#include "PlaneObj.h"
class ShadowPlane :
	public PlaneObj
{
public:
	ShadowPlane(Vec3<float> pos, Texture2D texture, std::string tag, DisplayableObject& parent, float verticalOffset);
	virtual ~ShadowPlane();
	virtual void Update(long tCurrent);

private:
	DisplayableObject& parent;
	float verticalOffset;
};

