#include "BoundingBox.h"
#include <GL/glut.h>

#include <iostream>

BoundingBox::BoundingBox(float width, float height, float depth, const Vec3<float>& parentPos)
	:width(width), height(height), depth(depth), parentPos(parentPos)
{
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::Render()
{





	glPushMatrix();
	glColor4f(1.f, 0.f, 0.f, 1.f);
	//Set drawing scale
	glScalef(1, 1, 1);

	glBegin(GL_LINE_LOOP);
	glVertex3f(-width, height, depth);
	glVertex3f(width, height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(-width, -height, depth);
	glEnd();
	// FAR SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(width, height, -depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(-width, -height, -depth);
	glVertex3f(width, -height, -depth);
	glEnd();
	// BOTTOM SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(-width, -height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width,-height, -depth);
	glVertex3f(-width, -height, -depth);
	glEnd();
	// TOP SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(width, height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	glEnd();
	// LEFT SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(-width, width, -depth);
	glVertex3f(-width, width, depth);
	glVertex3f(-width, -height, depth);
	glVertex3f(-width, -height, -depth);
	glEnd();
	// RIGHT SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(width, width, depth);
	glVertex3f(width, width, -depth);
	glVertex3f(width, -height, -depth);
	glVertex3f(width, -height, depth);
	glEnd();


	glPopMatrix();
}

std::vector<Vec3<float>> BoundingBox::GetIndicies()
{
	//Need to acount for rotation


	//Format = (Front/Rear)(Top/Bot)(Left/Right)
	Vec3<float> RTL = parentPos - Vec3<float>(width, -height, depth);
	Vec3<float> RTR = parentPos - Vec3<float>(-width, -height, depth);
	Vec3<float> RBL = parentPos - Vec3<float>(width, height, depth);
	Vec3<float> RBR = parentPos - Vec3<float>(-width, height, depth);
	Vec3<float> FTL = parentPos - Vec3<float>(width, -height, -depth);
	Vec3<float> FTR = parentPos - Vec3<float>(-width, -height, -depth);
	Vec3<float> FBL = parentPos - Vec3<float>(width, height, -depth);
	Vec3<float> FBR = parentPos - Vec3<float>(-width, height, -depth);


	std::vector<Vec3<float>> ind;
	ind.push_back(RTL);
	ind.push_back(RTR);
	ind.push_back(RBL);
	ind.push_back(RBR);
	ind.push_back(FTL);
	ind.push_back(FTR);
	ind.push_back(FBL);
	ind.push_back(FBR);


	/*std::cout << "POINTS" << std::endl; 
	for (Vec3<float> midP : ind)
		std::cout << midP.x << " " << midP.y << " " << midP.z << std::endl;*/

	return ind;
}
