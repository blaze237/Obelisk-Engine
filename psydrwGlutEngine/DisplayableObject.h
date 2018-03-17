#pragma once
#include <GL/glut.h>
#include "Vec3.h"
class DisplayableObject
{
public:
	DisplayableObject(Vec3<float> pos, Vec3<float> scale = Vec3<float>(1,1,1), Vec3<float> orientation = Vec3<float>(0,0,0));
	~DisplayableObject();

	//Calls your render function and handles matrix translations needed to draw at the correct position, scale and orientation. 
	//Not intended to be overiden
	void RenderObject();

	//Overide this with your own render code. Dont call directly, is called by RenderObject
	virtual void Render() = 0;
	//Default empty update. Overide for logic/animations/phsyics etc
	virtual void Update(long tCurrent);



protected:

	Vec3<float> pos;
	Vec3<float> scale;
	Vec3<float> orientation;

};

