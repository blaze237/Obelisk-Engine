#include "DisplayableObject.h"
#include <iostream>


DisplayableObject::DisplayableObject(Vec3<float> pos, Vec3<float> bBoxSize, std::string tag)
	:pos(pos), scale(Vec3<float>(1,1,1)), orientation(Vec3<float>(0,0,0)), TAG(tag), bBox(bBoxSize.x, bBoxSize.y, bBoxSize.z, this->pos, this->orientation)
{


}


DisplayableObject::~DisplayableObject()
{
}
void DisplayableObject::RenderObject()
{
	//Render the box before applying scaling
	bBox.Render();

	glPushMatrix();
	//Move drawing to object location
	glTranslatef(pos.x, pos.y, pos.z);

	//Orient drawing according to object orientation
	//Associative multiplication, so final rotation call done first
	glRotatef(orientation.z, 0, 0, 1);
	glRotatef(orientation.y, 0, 1, 0);
	glRotatef(orientation.x, 1, 0, 0);


	

	//Set drawing scale
	glScalef(scale.x, scale.y, scale.z);

	//Draw the object
	Render();

	glPopMatrix();


	


}
void DisplayableObject::Update(long tCurrent)
{
}

void DisplayableObject::OnCollide(std::string tag)
{
}
