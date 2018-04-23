#pragma once
#include "DisplayableObject.h"
class Sphere :
	public DisplayableObject
{
public:
	Sphere(Vec3<float> pos, std::string tag, Texture2D texture);
	~Sphere();



	inline void SetResolution(float v)
	{
		resolution = v;
	}
	inline void SetTexTiling(float v)
	{
		texTilingX = texTilingZ = v;
	}
	inline void SetTexTilingX(float v)
	{
		texTilingX = v;
	}
	inline void SetTexTilingZ(float v)
	{
		texTilingZ = v;
	}

	virtual void Render();

private: 

	//Convert from phi and theta to co-ordinate in cartesian co-ordinate assuming unit radius
	inline Vec3<float> SphericalToCartesian(float phi, float theta)
	{
		return Vec3<float>(cos(phi) * sin(theta), cos(theta) , sin(phi) * sin(theta));
	}




	Texture2D texture;
	float texTilingX = 1;
	float texTilingZ = 1;
	float resolution = 15;
};

