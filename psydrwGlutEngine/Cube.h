#pragma once
#include "DisplayableObject.h"
class Cube :
	public DisplayableObject
{
public:
	Cube(Vec3<float> pos, std::string tag, Texture2D texture);
	Cube(Vec3<float> pos, std::string tag, Texture2D texture, float texTiling);
	Cube(Vec3<float> pos, std::string tag, Texture2D texture, float texTilingX, float texTilingZ);

	virtual ~Cube();

	virtual void Render();

private:
	Texture2D texture;
	float texTilingX = 1;
	float texTilingZ = 1;
};

