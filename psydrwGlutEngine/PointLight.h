#pragma once
#include "Light.h"
#include <random>
class PointLight :
	public Light
{
public:
	PointLight(Vec3<float>pos, Colour ambient, Vec3<int> diffuse, Colour specular);
	virtual ~PointLight();

	virtual void Render(GLenum lightID);
	//Hanlde any movement etc
	virtual void Update(long tCurrent);

	inline virtual void SetRadius(float r)
	{
		radius = r;
		radBase = r;
	}

	inline float GetRadius() const
	{
		return radius;
	}


private:

	//Need to keep ref to base value of radius to keep flickering clamped
	float radBase = 5;

	//Wether to apply pseudo random flickering to the lights radius
	bool flicker = true;
	long flickerRate = 80;
	float flickerIntensity = 0.6;
	//Used for flipping the effect of flickering eahc update
	int flickerSign = 1;
	//Seed used for flicker generation
	std::random_device seed;
	//RNG used for flicker generation
	std::mt19937 rng;
	//Range of flicker values to pick from
	std::uniform_real_distribution<float> flickerRange;
	//Keep track of how much time has passed since last flicker 
	long tSinceUpdate = 0;
	long lastTime = 0;
};

