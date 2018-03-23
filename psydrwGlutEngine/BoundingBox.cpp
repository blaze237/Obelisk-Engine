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

void BoundingBox::Render() const
{
	//Grab the position of each index
	std::vector<Vec3<float>> ind = GetIndicies();

	glPushMatrix();
	glColor4f(1.f, 0.f, 0.f, 1.f);
	//Set drawing scale
	glScalef(1, 1, 1);


	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(ind[0].x, ind[0].y, ind[0].z); // FTL
	glVertex3f(ind[1].x, ind[1].y, ind[1].z); //FTR
	glVertex3f(ind[2].x, ind[2].y, ind[2].z); //FBR
	glVertex3f(ind[3].x, ind[3].y, ind[3].z); //FBL
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

	glPopMatrix();
}

std::vector<Vec3<float>> BoundingBox::GetIndicies() const
{
	//Get indicies for cube centered at origin with no rotation
	std::vector<Vec3<float>> ind;
	ind.push_back(Vec3<float>(-width, height, depth)); //FTL
	ind.push_back(Vec3<float>(width, height, depth)); //FTR
	ind.push_back(Vec3<float>(width, -height, depth)); //FBR
	ind.push_back(Vec3<float>(-width, -height, depth)); //FBL
	ind.push_back(Vec3<float>(width, height, -depth)); //RTR
	ind.push_back(Vec3<float>(-width, height, -depth)); //RTL
	ind.push_back(Vec3<float>(-width, -height, -depth)); //RBL
	ind.push_back(Vec3<float>(width, -height, -depth)); //RBR


	//Apply parent rotation to the indicies
	if (parentRot.x != 0 || parentRot.y != 0 || parentRot.z != 0)
	{
		for (int i = 0; i < 8; ++i)
			ind[i] = MathHelp::RotatePoint(ind[i], parentRot);
	}

	//Apply parent translation to the indicies
	ind[0] = parentPos + ind[0];
	ind[1] = parentPos + ind[1];
	ind[2] = parentPos + ind[2];
	ind[3] = parentPos + ind[3];
	ind[4] = parentPos + ind[4];
	ind[5] = parentPos + ind[5];
	ind[6] = parentPos + ind[6];
	ind[7] = parentPos + ind[7];

	return ind;
}

std::vector<BoxFace> BoundingBox::GetFaces() const
{
	//Grab the box points
	std::vector<Vec3<float>> ind = GetIndicies();

	//Front Face
	BoxFace front(ind[0], ind[2], ind[1]);
	//Back Face
	BoxFace back(ind[4], ind[7], ind[5]);
	//Top face
	BoxFace top(ind[5], ind[0], ind[4]);
	//Bottom face
	BoxFace bot(ind[7], ind[2], ind[6]);
	//Left face
	BoxFace left(ind[5], ind[6], ind[0]);
	//Right face
	BoxFace right(ind[1], ind[2], ind[4]);

	std::vector<BoxFace> faces;
	faces.push_back(front);
	faces.push_back(back);
	faces.push_back(top);
	faces.push_back(bot);
	faces.push_back(left);
	faces.push_back(right);

	return faces;
}
