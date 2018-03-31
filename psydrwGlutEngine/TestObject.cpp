#include "TestObject.h"
#include <iostream>
#include "MathHelp.h"

TestObject::TestObject(Vec3<float> pos, Texture2D texture, std::string tag)
	:DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), texture(texture)
{
	kinematic = false;
//	renderCollider = true;
	collidable = true;
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
	////Get the ellapsed time since the last rotation occured
	//long dt = tCurrent - lastTime;
	//if (dt > timeStep)
	//{
	//	//Get the new rotation of the camera
	//	theta = theta < (360) ? (theta + dt / timeStep) : 0;
	//	lastTime = tCurrent;
	//	orientation.x = MathHelp::Clamp( (float)theta, 0.f, 360.0f);
	//	orientation.y = MathHelp::Clamp( (float)theta, 0.f, 360.0f);

	//}
}

void TestObject::drawCube(float radius)
{


	// Enable setting the colour of the material the cube is made from
	// as well as the material for blending.
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture.getID());

	glBegin(GL_QUADS);

	// draw the front face

	// set the colour of the front face
	//glColor3f(1.0f, 0.0f, 0.0f);

	// set the normal of the front face
	glNormal3f(0.0f, 0.0f, 1.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	// draw the back face

	// set the colour of the front face
	//glColor3f(0.0f, 1.0f, 0.0f);

	// set the normal of the front face
	glNormal3f(0.0f, 0.0f, -1.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// draw the left face

	// set the colour of the front face
//	glColor3f(0.0f, 0.0f, 1.0f);

	// set the normal of the front face
	glNormal3f(-1.0f, 0.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// draw the right face

	// set the colour of the front face
	//glColor3f(0.0f, 1.0f, 1.0f);

	// set the normal of the front face
	glNormal3f(1.0f, 0.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	// draw the top face

	// set the colour of the front face
	//glColor3f(1.0f, 1.0f, 0.0f);

	// set the normal of the front face
	glNormal3f(0.0f, 1.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	// draw the bottom face

	// set the colour of the front face
	//glColor3f(1.0f, 0.0f, 1.0f);

	// set the normal of the front face
	glNormal3f(0.0f, -1.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glEnd();

	// Stop blending textures and colours
	glDisable(GL_COLOR_MATERIAL);

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);

	//glPushMatrix();

	////Start Drawing the cube
	//glBegin(GL_TRIANGLES);

	////FRONT FACE
	//glColor3f(1.0f, 0.0f, 0.0f);
	////Triangle 1
	//glVertex3f(radius, -radius, radius);
	//glVertex3f(radius, radius, radius);
	//glVertex3f(-radius, radius, radius);
	////Triangle 2
	//glVertex3f(-radius, radius, radius);
	//glVertex3f(-radius, -radius, radius);
	//glVertex3f(radius, -radius, radius);

	////BACK FACE
	//glColor3f(0.0f, 1.0f, 0.0f);
	////Triangle 1
	//glVertex3f(radius, -radius, -radius);
	//glVertex3f(-radius, -radius, -radius);
	//glVertex3f(-radius, radius, -radius);
	////Triangle 2
	//glVertex3f(-radius, radius, -radius);
	//glVertex3f(radius, radius, -radius);
	//glVertex3f(radius, -radius, -radius);

	////TOP FACE
	//glColor3f(0.0f, 0.0f, 1.0f);
	////Triangle 1
	//glVertex3f(radius, radius, radius);
	//glVertex3f(radius, radius, -radius);
	//glVertex3f(-radius, radius, -radius);
	////Triangle 2
	//glVertex3f(-radius, radius, -radius);
	//glVertex3f(-radius, radius, radius);
	//glVertex3f(radius, radius, radius);

	////BOTTOM FACE
	//glColor3f(1.0f, 1.0f, 0.0f);
	////Triangle 1
	//glVertex3f(radius, -radius, radius);
	//glVertex3f(-radius, -radius, radius);
	//glVertex3f(-radius, -radius, -radius);
	////Triangle 2
	//glVertex3f(-radius, -radius, -radius);
	//glVertex3f(radius, -radius, -radius);
	//glVertex3f(radius, -radius, radius);

	////LEFT FACE 
	//glColor3f(1.0f, 0.0f, 1.0f);
	////Triangle 1
	//glVertex3f(-radius, -radius, radius);
	//glVertex3f(-radius, radius, radius);
	//glVertex3f(-radius, radius, -radius);
	////Triangle 2
	//glVertex3f(-radius, radius, -radius);
	//glVertex3f(-radius, -radius, -radius);
	//glVertex3f(-radius, -radius, radius);

	////RIGHT FACE
	//glColor3f(0.0f, 1.0f, 1.0f);
	////Triangle 1
	//glVertex3f(radius, -radius, radius);
	//glVertex3f(radius, -radius, -radius);
	//glVertex3f(radius, radius, -radius);
	////Triangle 2
	//glVertex3f(radius, radius, -radius);
	//glVertex3f(radius, radius, radius);
	//glVertex3f(radius, -radius, radius);

	//glEnd();

	//glPopMatrix();
}
