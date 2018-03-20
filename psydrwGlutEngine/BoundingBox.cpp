#include "BoundingBox.h"
#include <GL/glut.h>



BoundingBox::BoundingBox(float width, float height, float depth)
	:width(width), height(height), depth(depth)
{
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::Render()
{
	glPushMatrix();
	glColor4f(1.f, 0.f, 0.f, 1.f);

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
