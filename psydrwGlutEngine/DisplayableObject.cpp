#include "DisplayableObject.h"
#include <iostream>

unsigned int DisplayableObject::nextID = 0;


DisplayableObject::DisplayableObject(Vec3<float> pos, Vec3<float> bBoxSize, std::string tag)
	:pos(pos), scale(Vec3<float>(1,1,1)), orientation(Vec3<float>(0,0,0)), TAG(tag), bBox(bBoxSize.x, bBoxSize.y, bBoxSize.z, this->pos, this->orientation, this->scale), ID(nextID++)
{


}


DisplayableObject::~DisplayableObject()
{
}
void DisplayableObject::RenderObject()
{
	//Render the box before applying properties
	if(renderCollider)
		bBox.Render();

	if (!renderable)
		return;

	//Each object works on its own matrix and attribute stack
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//Disable back face culling if needed
	if(!cullBackFaces)
		glDisable(GL_CULL_FACE);

	//Set material properites
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmis);
	glMateriali(GL_FRONT, GL_SHININESS, matShin);

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

	//Re-enable back face culling
	if(!cullBackFaces)
		glEnable(GL_CULL_FACE);


	glPopAttrib();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();
}
void DisplayableObject::Update(long tCurrent)
{
}

bool DisplayableObject::OnCollide(std::string tag)
{
	return false;
}

void DisplayableObject::OnTrigger(std::string tag)
{
}
