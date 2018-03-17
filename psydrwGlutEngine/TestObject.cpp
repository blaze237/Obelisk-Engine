#include "TestObject.h"
#include <iostream>
#include "MathHelp.h"

TestObject::TestObject(Vec3<float> pos)
	:DisplayableObject(pos)
{
	scale.x = scale.y = scale.z = 1.5;
}


TestObject::~TestObject()
{
}

void TestObject::Render()
{
	drawCube(5);
}

void TestObject::Update(long tCurrent)
{
	//Get the ellapsed time since the last rotation occured
	long dt = tCurrent - lastTime;
	if (dt > timeStep)
	{
		//Get the new rotation of the camera
		theta = theta < (360) ? (theta + dt / timeStep) : 0;
		lastTime = tCurrent;
		orientation.x = MathHelp::Clamp( (float)theta, 0.f, 360.0f);
		orientation.y = MathHelp::Clamp( (float)theta, 0.f, 360.0f);

	}
}

void TestObject::drawCube(float radius)
{
	glPushMatrix();

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

	glPopMatrix();
}
