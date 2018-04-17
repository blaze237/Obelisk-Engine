#pragma once
#include "DisplayableObject.h"
#include "Texture2D.h"
class Cylinder :
	public DisplayableObject
{
public:
	Cylinder(Vec3<float> pos, std::string tag, Texture2D tex);
	Cylinder(Vec3<float> pos, std::string tag, Texture2D tex, float texTiling);
	Cylinder(Vec3<float> pos, std::string tag, Texture2D tex, float texTilingX, float texTilingZ);

	virtual ~Cylinder();

	virtual void Render();

private:
	Texture2D texture;
	float texTilingX = 1;
	float texTilingZ = 1;
};

