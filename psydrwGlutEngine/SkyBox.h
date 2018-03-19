#pragma once
#include <vector>
#include "Vec3.h"
#include "Texture2D.h"
#include <iostream>
class SkyBox
{
public:
	SkyBox(const std::vector<Texture2D>& texts);
	~SkyBox();

	void Render();


	inline Vec3<float> GetScale() const
	{
		return scale;
	}
	
	inline void SetScale(float s)
	{
		std::cout << s << std::endl;
		scale.x = scale.y = scale.z = s;
	}
	inline void SetScale(const Vec3<float>& s)
	{
		scale = s;
	}


private:
	Vec3<float> scale;
	std::vector<Texture2D> textures;
};

