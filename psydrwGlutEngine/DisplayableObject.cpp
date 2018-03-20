#include "DisplayableObject.h"



DisplayableObject::DisplayableObject(Vec3<float> pos, Vec3<float> bBoxSize, Vec3<float> scale, Vec3<float> orientation )
	:pos(pos), scale(scale), orientation(orientation), bBox(bBoxSize.x, bBoxSize.y, bBoxSize.z)
{

}


DisplayableObject::~DisplayableObject()
{
}
void DisplayableObject::RenderObject()
{
	glPushMatrix();
	//Move drawing to object location
	glTranslatef(pos.x, pos.y, pos.z);

	//Orient drawing according to object orientation
	glRotatef(orientation.x, 1, 0, 0);
	glRotatef(orientation.y, 0, 1, 0);
	glRotatef(orientation.z, 0, 0, 1);

	//Set drawing scale
	glScalef(scale.x, scale.y, scale.z);

	//Draw the object
	Render();

	glPopMatrix();

}
void DisplayableObject::Update(long tCurrent)
{
}
