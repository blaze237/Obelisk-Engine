#pragma once
#include "DisplayableObject.h"
class Plane :
	public DisplayableObject
{
public:
	Plane(Vec3<float> pos, Texture2D texture, std::string tag, int resolution);
	Plane(Vec3<float> pos, Texture2D texture, std::string tag, int resolution, float texTiling);	
	Plane(Vec3<float> pos, Texture2D texture, std::string tag, int resolution, float texTilingX, float texTilingZ);

	virtual ~Plane();

	virtual void Render();

private:
	int resolution;
	float texTilingX = 1;
	float texTilingZ = 1;
	Texture2D texture;
};

