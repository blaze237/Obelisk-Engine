#include "TestObject.h"



TestObject::TestObject()
{
}


TestObject::~TestObject()
{
}

void TestObject::Render()
{
	//Set draw position
	glTranslatef(0.f, 0.f, -50.f);
	//Slowly rotate the draw position
	glRotatef(theta, 1, 1, 0);
	drawCube(5);
}

void TestObject::Update(long tCurrent)
{
	//Get the ellapsed time since the last frame was drawn
	long dt = tCurrent - lastTime;
	if (dt > timeStep)
	{
		//Get the new rotation of the camera
		theta = theta < (360) ? ++theta : 0;
		lastTime = tCurrent;
	}
}

void TestObject::drawCube(float radius)
{
	//Start Drawing the cube
	glBegin(GL_TRIANGLES);

	//FRONT FACE
	glColor3f(1.0f, 0.0f, 0.0f);
	//Triangle 1
	glVertex3f(radius, -radius, radius);
	glVertex3f(radius, radius, radius);
	glVertex3f(-radius, radius, radius);
	//Triangle 2
	glVertex3f(-radius, radius, radius);
	glVertex3f(-radius, -radius, radius);
	glVertex3f(radius, -radius, radius);

	//BACK FACE
	glColor3f(0.0f, 1.0f, 0.0f);
	//Triangle 1
	glVertex3f(radius, -radius, -radius);
	glVertex3f(-radius, -radius, -radius);
	glVertex3f(-radius, radius, -radius);
	//Triangle 2
	glVertex3f(-radius, radius, -radius);
	glVertex3f(radius, radius, -radius);
	glVertex3f(radius, -radius, -radius);

	//TOP FACE
	glColor3f(0.0f, 0.0f, 1.0f);
	//Triangle 1
	glVertex3f(radius, radius, radius);
	glVertex3f(radius, radius, -radius);
	glVertex3f(-radius, radius, -radius);
	//Triangle 2
	glVertex3f(-radius, radius, -radius);
	glVertex3f(-radius, radius, radius);
	glVertex3f(radius, radius, radius);

	//BOTTOM FACE
	glColor3f(1.0f, 1.0f, 0.0f);
	//Triangle 1
	glVertex3f(radius, -radius, radius);
	glVertex3f(-radius, -radius, radius);
	glVertex3f(-radius, -radius, -radius);
	//Triangle 2
	glVertex3f(-radius, -radius, -radius);
	glVertex3f(radius, -radius, -radius);
	glVertex3f(radius, -radius, radius);

	//LEFT FACE 
	glColor3f(1.0f, 0.0f, 1.0f);
	//Triangle 1
	glVertex3f(-radius, -radius, radius);
	glVertex3f(-radius, radius, radius);
	glVertex3f(-radius, radius, -radius);
	//Triangle 2
	glVertex3f(-radius, radius, -radius);
	glVertex3f(-radius, -radius, -radius);
	glVertex3f(-radius, -radius, radius);

	//RIGHT FACE
	glColor3f(0.0f, 1.0f, 1.0f);
	//Triangle 1
	glVertex3f(radius, -radius, radius);
	glVertex3f(radius, -radius, -radius);
	glVertex3f(radius, radius, -radius);
	//Triangle 2
	glVertex3f(radius, radius, -radius);
	glVertex3f(radius, radius, radius);
	glVertex3f(radius, -radius, radius);

	glEnd();
}
