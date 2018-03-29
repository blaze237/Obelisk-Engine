#include "BoundingBox.h"
#include <GL/glut.h>
#include "MathHelp.h"
#include <iostream>

BoundingBox::BoundingBox(float width, float height, float depth, const Vec3<float>& parentPos, const Vec3<float>& parentRot, Vec3<float>& parentScale, bool trigger)
	:width(width), height(height), depth(depth), parentPos(parentPos), parentRot(parentRot), parentScale(parentScale), trigger(trigger)
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
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
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

	glPopAttrib();
	glPopMatrix();}

std::vector<Vec3<float>> BoundingBox::GetIndicies(Vec3<float> posOffset, Vec3<float> rotOffset) const
{
	//Apply scaling to the bounding box
	float width = this->width * parentScale.x;
	float height = this->height * parentScale.y;
	float depth = this->depth * parentScale.z;

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

	//Note that the translations and rotations appear to be being done in the reverse order to that used in the parent displayable objects RenderObject method. 
	//However, this isnt actualy the case, the discrepancy is due to the fact that opengl matrix stack transforms are actualy applied in the opposite order to which they are called in.
	//As opposed to the following custom transform code, which applies transforms in the order they are called.

	//Apply parent rotation to the indicies so that they are correclty placed in cube space
	if (parentRot.x != 0 || parentRot.y != 0 || parentRot.z != 0)
	{
		for (int i = 0; i < 8; ++i)
			ind[i] = MathHelp::RotatePoint(ind[i], parentRot + rotOffset);
	}

	//Apply parent translation to the indicies to convert positions into world
	ind[0] = parentPos + ind[0] + posOffset;
	ind[1] = parentPos + ind[1] + posOffset;
	ind[2] = parentPos + ind[2] + posOffset;
	ind[3] = parentPos + ind[3] + posOffset;
	ind[4] = parentPos + ind[4] + posOffset;
	ind[5] = parentPos + ind[5] + posOffset;
	ind[6] = parentPos + ind[6] + posOffset;
	ind[7] = parentPos + ind[7] + posOffset;

	return ind;
}

std::vector<BoxFace> BoundingBox::GetFaces(Vec3<float> posOffset, Vec3<float> rotOffset) const
{
	//Grab the box points
	std::vector<Vec3<float>> ind = GetIndicies(posOffset);

	//Front Face
	BoxFace front(ind[0], ind[2], ind[1], "Front");
	//Back Face
	BoxFace back(ind[4], ind[7], ind[5], "Back");
	//Top face
	BoxFace top(ind[5], ind[0], ind[4], "Top");
	//Bottom face
	BoxFace bot(ind[7], ind[2], ind[6], "bot");
	//Left face
	BoxFace left(ind[5], ind[6], ind[0], "Left");
	//Right face
	BoxFace right(ind[1], ind[2], ind[4], "Right");

	std::vector<BoxFace> faces;
	faces.push_back(front);
	faces.push_back(back);
	faces.push_back(top);
	faces.push_back(bot);
	faces.push_back(left);
	faces.push_back(right);

	return faces;
}
