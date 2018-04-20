#pragma once
#include "Light.h"
class Spotlight :
	public Light
{
public:
	Spotlight(Vec3<float>pos, Colour ambient, Vec3<int> diffuse, Colour specular, Vec3<float> direction);
	Spotlight(Vec3<float>pos, Colour ambient, Vec3<int> diffuse, Colour specular, Vec3<float> direction, float radius);
	virtual ~Spotlight();

	virtual void Render(GLenum lightID);
	//Hanlde any movement etc
	virtual void Update(long tCurrent)
	{

	}

	

	inline void SetDirection(Vec3<float> direction)
	{
		dir[0] = direction.x;
		dir[1] = direction.y;
		dir[2] = direction.z;
	}

	inline void SetCutOff(int cOff)
	{
		cuttOff = cOff;
	}

	inline void SetExponent(int exp)
	{
		exponent = exp;
	}




private:
	//Direction the spotlight is shining in
	float dir[3];
	//What angle to cut off the light at. Higher values -> more spread
	int cuttOff = 45;
	//Controlls the intensity of the light with angle, lower -> more uniform and more spread
	int exponent = 25;


};

