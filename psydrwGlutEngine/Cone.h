#pragma once
#include "DisplayableObject.h"
class Cone :
	public DisplayableObject
{
public:
	Cone(Vec3<float> pos, std::string tag, Texture2D tex);
	Cone(Vec3<float> pos, std::string tag, Texture2D tex, float texTiling);
	Cone(Vec3<float> pos, std::string tag, Texture2D tex, float texTilingX, float texTilingZ);
	virtual ~Cone();

	virtual void Render();

private:
	Texture2D texture;
	float texTilingX = 1;
	float texTilingZ = 1;
};

