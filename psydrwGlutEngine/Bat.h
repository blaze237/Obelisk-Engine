#pragma once
#include "DisplayableObject.h"
class Bat :
	public DisplayableObject
{
public:
	Bat(Vec3<float> pos, std::vector<Vec3<float>> velocities, long moveRate);
	virtual ~Bat();

	virtual void Render();
	virtual void Update(long tCurrent);

private:

	//Allign the bat in y rotation only automaticaly based on its velocity
	void AllignBat();
	void DrawWing(Texture2D& tex);
	void DrawBody();
	//Convert from phi and theta to co-ordinate in cartesian co-ordinate assuming unit radius. Helper function used by DrawBody
	inline Vec3<float> SphericalToCartesian(float phi, float theta)
	{
		return Vec3<float>(cos(phi) * sin(theta), cos(theta), sin(phi) * sin(theta));
	}

	//Keep track of how much time has passed since last updated wing angle
	long tSinceFlap = 0;
	//Keep track of how much time has passed since last updated the bats velocity
	long tSinceVelChng = 0;
	long lastTime = 0;
	//How long to wait between updating angle of wings
	long wingFlapRate =7;
	//How long to wait between switching to next velocity in the array
	long moveRate;
	//Array of velocities to apply to the bat as animation
	std::vector<Vec3<float>> velocities;
	int velIndex = 0;

	const float wingAngleMax = 30;
	int angleDelta = 1;
	float wingAngle = 0;
	Texture2D bodyTex;
	Texture2D leftWingTex;
	Texture2D rightWingTex;

};

