#include "BoundingBox.h"
#include <GL/glut.h>
#include "MathHelp.h"
#include <iostream>

BoundingBox::BoundingBox(float width, float height, float depth, const Vec3<float>& parentPos, const Vec3<float>& parentRot)
	:width(width), height(height), depth(depth), parentPos(parentPos), parentRot(parentRot)
{
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::Render()
{

	std::vector<Vec3<float>> ind = GetIndicies();


	glPushMatrix();
	glColor4f(1.f, 0.f, 0.f, 1.f);
	//Set drawing scale
	glScalef(1, 1, 1);




	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(ind[0].x, ind[0].y, ind[0].z);
	glVertex3f(ind[1].x, ind[1].y, ind[1].z);
	glVertex3f(ind[2].x, ind[2].y, ind[2].z);
	glVertex3f(ind[3].x, ind[3].y, ind[3].z);
	glEnd();
	// FAR SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(ind[4].x, ind[4].y, ind[4].z);
	glVertex3f(ind[5].x, ind[5].y, ind[5].z);
	glVertex3f(ind[6].x, ind[6].y, ind[6].z);
	glVertex3f(ind[7].x, ind[7].y, ind[7].z);
	glEnd();
	// BOTTOM SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(ind[3].x, ind[3].y, ind[3].z); //fbl
	glVertex3f(ind[2].x, ind[2].y, ind[2].z); //fbr
	glVertex3f(ind[7].x, ind[7].y, ind[7].z); //rbr
	glVertex3f(ind[6].x, ind[6].y, ind[6].z); //rbl
	glEnd();
	// TOP SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(ind[1].x, ind[1].y, ind[1].z); //ftr
	glVertex3f(ind[0].x, ind[0].y, ind[0].z); //ftl
	glVertex3f(ind[5].x, ind[5].y, ind[5].z); //rtl
	glVertex3f(ind[4].x, ind[4].y, ind[4].z); //rtr
	glEnd();
	// LEFT SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(ind[5].x, ind[5].y, ind[5].z); //rtl
	glVertex3f(ind[0].x, ind[0].y, ind[0].z); //ftl
	glVertex3f(ind[3].x, ind[3].y, ind[3].z); //fbl
	glVertex3f(ind[6].x, ind[6].y, ind[6].z); //rbl
	glEnd();
	// RIGHT SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(ind[1].x, ind[1].y, ind[1].z); //ftr
	glVertex3f(ind[4].x, ind[4].y, ind[4].z); //rtr
	glVertex3f(ind[7].x, ind[7].y, ind[7].z); //rbr
	glVertex3f(ind[2].x, ind[2].y, ind[2].z); //fbr
	glEnd();


	////Front
	//glBegin(GL_LINE_LOOP);
	//glVertex3f(-width, height, depth);
	//glVertex3f(width, height, depth);
	//glVertex3f(width, -height, depth);
	//glVertex3f(-width, -height, depth);
	//glEnd();
	//// FAR SIDE
	//glBegin(GL_LINE_LOOP);
	//glVertex3f(width, height, -depth);
	//glVertex3f(-width, height, -depth);
	//glVertex3f(-width, -height, -depth);
	//glVertex3f(width, -height, -depth);
	//glEnd();
	//// BOTTOM SIDE
	//glBegin(GL_LINE_LOOP);
	//glVertex3f(-width, -height, depth);
	//glVertex3f(width, -height, depth);
	//glVertex3f(width,-height, -depth);
	//glVertex3f(-width, -height, -depth);
	//glEnd();
	//// TOP SIDE
	//glBegin(GL_LINE_LOOP);
	//glVertex3f(width, height, depth);
	//glVertex3f(-width, height, depth);
	//glVertex3f(-width, height, -depth);
	//glVertex3f(width, height, -depth);
	//glEnd();
	//// LEFT SIDE
	//glBegin(GL_LINE_LOOP);
	//glVertex3f(-width, width, -depth); //width = > height???
	//glVertex3f(-width, width, depth);
	//glVertex3f(-width, -height, depth);
	//glVertex3f(-width, -height, -depth);
	//glEnd();
	//// RIGHT SIDE
	//glBegin(GL_LINE_LOOP);
	//glVertex3f(width, width, depth);
	//glVertex3f(width, width, -depth);
	//glVertex3f(width, -height, -depth);
	//glVertex3f(width, -height, depth);
	//glEnd();


	glPopMatrix();
}

std::vector<Vec3<float>> BoundingBox::GetIndicies()
{
	//Need to acount for rotation





	//Format = (Front/Rear)(Top/Bot)(Left/Right)
	/*Vec3<float> RTL = parentPos - Vec3<float>(width, -height, depth);
	Vec3<float> RTR = parentPos - Vec3<float>(-width, -height, depth);
	Vec3<float> RBL = parentPos - Vec3<float>(width, height, depth);
	Vec3<float> RBR = parentPos - Vec3<float>(-width, height, depth);
	Vec3<float> FTL = parentPos - Vec3<float>(width, -height, -depth);
	Vec3<float> FTR = parentPos - Vec3<float>(-width, -height, -depth);
	Vec3<float> FBL = parentPos - Vec3<float>(width, height, -depth);
	Vec3<float> FBR = parentPos - Vec3<float>(-width, height, -depth);*/


	Vec3<float> RTL =  Vec3<float>(width, -height, depth);
	Vec3<float> RTR =  Vec3<float>(-width, -height, depth);
	Vec3<float> RBL = Vec3<float>(width, height, depth);
	Vec3<float> RBR =  Vec3<float>(-width, height, depth);
	Vec3<float> FTL =  Vec3<float>(width, -height, -depth);
	Vec3<float> FTR =  Vec3<float>(-width, -height, -depth);
	Vec3<float> FBL =  Vec3<float>(width, height, -depth);
	Vec3<float> FBR =  Vec3<float>(-width, height, -depth);



	std::vector<Vec3<float>> indtmp;
	indtmp.push_back(FTL);
	indtmp.push_back(FTR);
	indtmp.push_back(FBR);
	indtmp.push_back(FBL);

	indtmp.push_back(RTR);
	indtmp.push_back(RTL);
	indtmp.push_back(RBL);
	indtmp.push_back(RBR);


	//If not axis aligned, then must transform these points to match parent orientation
	if (parentRot.x != 0 || parentRot.y != 0 || parentRot.z != 0)
	{

		for (int i = 0; i < 8; ++i)
		{

			indtmp[i] = MathHelp::RotatePoint(indtmp[i], parentRot);
		}

		/*for (Vec3<float> i : ind)
		{
		i = MathHelp::RotatePoint(i, parentRot);
		}*/
	}


	FTL = parentPos - indtmp[0];
	FTR = parentPos - indtmp[1];
	FBR =  parentPos - indtmp[2];
	FBL = parentPos - indtmp[3];
	RTR = parentPos - indtmp[4];
	RTL = parentPos - indtmp[5];
	RBL = parentPos - indtmp[6];
	RBR = parentPos - indtmp[7];






	std::vector<Vec3<float>> ind;
	ind.push_back(FTL);
	ind.push_back(FTR);
	ind.push_back(FBR);
	ind.push_back(FBL);

	ind.push_back(RTR);
	ind.push_back(RTL);
	ind.push_back(RBL);
	ind.push_back(RBR);


	/*ind.push_back(RTL);
	ind.push_back(RTR);
	ind.push_back(RBL);
	ind.push_back(RBR);
	ind.push_back(FTL);
	ind.push_back(FTR);
	ind.push_back(FBL);
	ind.push_back(FBR);*/

	

	return ind;
}
