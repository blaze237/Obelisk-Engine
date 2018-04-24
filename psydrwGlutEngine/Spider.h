#pragma once
#include "DisplayableObject.h"
class Spider :
	public DisplayableObject
{
public:
	Spider(Vec3<float> pos, std::vector<Vec3<float>> velocities, long moveRate);
	virtual ~Spider();


	virtual void Render();
	virtual void Update(long tCurrent);

private:
	//Allign the bat in y such that the normal of its bbox's front face is parralell with the normalised velocity in the xz plane
	void AllignSpider();
	void DrawLeg();
	void DrawLegSection(Texture2D& texture);
	void DrawBodyPart(Texture2D& tex);
	//Convert from phi and theta to co-ordinate in cartesian co-ordinate assuming unit radius. Helper function used by DrawBody
	inline Vec3<float> SphericalToCartesian(float phi, float theta)
	{
		return Vec3<float>(cos(phi) * sin(theta), cos(theta), sin(phi) * sin(theta));
	}

	//Keep track of how much time has passed since last updated leg angles
	long tSinceLegMove = 0;
	long tSinceLegMoveVert = 0;
	//Keep track of how much time has passed since last updated the spiders velocity
	long tSinceVelChng = 0;
	long lastTime = 0;
	//How long to wait between updating angle of legs
	long legMoveRate = 15;
	//How long to wait between switching to next velocity in the array
	long moveRate;
	//Array of velocities to apply to the spider as animation
	std::vector<Vec3<float>> velocities;
	int velIndex = 0;

	const float legAngleMax = 10;
	const float legVertAngleMax = 10;
	float legVertAngle = 0;
	float leftLeg1Angle = legAngleMax;
	float leftLeg2Angle = -legAngleMax;
	int angleDelta = 1;
	int vertAngleDelta = 1;
	Texture2D baseTex;
	Texture2D bodyTex;
};

