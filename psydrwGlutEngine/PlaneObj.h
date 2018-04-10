#pragma once
#include "DisplayableObject.h"
class PlaneObj :
	public DisplayableObject
{
public:
	PlaneObj(Vec3<float> pos, Texture2D texture, std::string tag, int resolution);
	PlaneObj(Vec3<float> pos, Texture2D texture, std::string tag, int resolution, float texTiling);	
	PlaneObj(Vec3<float> pos, Texture2D texture, std::string tag, int resolution, float texTilingX, float texTilingZ);

	virtual ~PlaneObj();

	virtual void Render();

private:
	int resolution;
	float texTilingX = 1;
	float texTilingZ = 1;
	Texture2D texture;
};

