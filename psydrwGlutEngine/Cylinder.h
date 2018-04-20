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

	inline void SetResolution(float r)
	{
		resolution = r;
	}

	inline float GetResolution() const
	{
		return resolution;
	}

	virtual ~Cylinder();
	virtual void Render();


private:
	Texture2D texture;
	float resolution = 0.05;
	float texTilingX = 1;
	float texTilingZ = 1;
};

