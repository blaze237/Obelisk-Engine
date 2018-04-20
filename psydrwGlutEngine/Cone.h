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

	inline void SetResolution(float r)
	{
		resolution = r;
	}

	inline float GetResolution() const
	{
		return resolution;
	}

	virtual void Render();

private:
	Texture2D texture;
	float resolution = 0.05;
	float texTilingX = 1;
	float texTilingZ = 1;
};

