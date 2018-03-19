#include "BoundingBox.h"
#include <GL/glut.h>



BoundingBox::BoundingBox(int width, int height, int depth)
	:width(width), height(height), depth(depth)
{
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::Render()
{
	glPushMatrix();
	glColor3f(0, 1, 0);
	//glScalef(1, height / width, depth / width);
	//glutWireCube(width);                                 

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
