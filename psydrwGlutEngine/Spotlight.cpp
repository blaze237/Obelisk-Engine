#include "Spotlight.h"
#include <cstdio>


Spotlight::Spotlight(Vec3<float>pos, Colour ambient, Colour diffuse, Colour specular, Vec3<float> direction)
	:Light(pos, ambient, diffuse, specular, false)
{
	dir[0] = direction.x;
	dir[1] = direction.y;
	dir[2] = direction.z;

	this->pos[3] = 0.0;
}



Spotlight::~Spotlight()
{
}

void Spotlight::Render(GLenum lightID)
{
	DebugRender();

	glEnable(GL_LIGHTING);
	//Set colours 
	glLightfv(lightID, GL_AMBIENT, amb);
	glLightfv(lightID, GL_DIFFUSE, dif);
	glLightfv(lightID, GL_SPECULAR, spec);
	//Set position
	glLightfv(lightID, GL_POSITION, pos);
	//Set direction
	glLightfv(lightID, GL_SPOT_DIRECTION, dir);
	//Set light cone paramaters
	glLightf(lightID, GL_SPOT_CUTOFF, cuttOff);
	glLightf(lightID, GL_SPOT_EXPONENT, exponent);
	//Set the attenuation values
	glLightf(lightID, GL_CONSTANT_ATTENUATION, constAttenuation);
	glLightf(lightID, GL_LINEAR_ATTENUATION, linearAttenuation);
	glLightf(lightID, GL_QUADRATIC_ATTENUATION, expAttenuation);

	glEnable(lightID);

}

void Spotlight::DebugRender()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glTranslatef(pos[0], pos[1], pos[2]);
	glColor4f(1.f, 1.f, 1.f, 1.f);
	//Set drawing scale
	glScalef(1, 1, 1);


	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1,1,1); // FTL
	glVertex3f(1, 1, 1); //FTR
	glVertex3f(1, -1, 1); //FBR
	glVertex3f(-1, -1, 1); //FBL
	glEnd();
	// FAR SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 1, -1); 
	glVertex3f(1, 1, -1); 
	glVertex3f(1, -1, -1); 
	glVertex3f(-1, -1, -1);
	glEnd();
	// BOTTOM SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, -1, 1); //fbl
	glVertex3f(1, -1, 1); //fbr
	glVertex3f(1, -1, -1); //rbr
	glVertex3f(-1, -1, -1); //rbl
	glEnd();
	// TOP SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 1, 1); //ftr
	glVertex3f(1, 1, 1); //tfl
	glVertex3f(1, 1, -1); //rtl
	glVertex3f(-1, 1, -1); //rtr
	glEnd();
	// LEFT SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 1, -1); //rtl
	glVertex3f(-1, 1, 1); //ftl
	glVertex3f(-1, -1, 1); //fbl
	glVertex3f(-1, -1, -1); //rbl
	glEnd();
	// RIGHT SIDE
	glBegin(GL_LINE_LOOP);
	glVertex3f(1, 1, -1); //ftr
	glVertex3f(1, 1, 1); //rtr
	glVertex3f(1, -1, 1); //rbr
	glVertex3f(1, -1, -1); //fbr
	glEnd();

	glPopAttrib();
	glPopMatrix();
}

