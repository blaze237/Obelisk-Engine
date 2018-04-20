#include "Light.h"



Light::Light(Vec3<float>position, Colour ambient, Vec3<int> diffuse, Colour specular, bool directional)
{
	//Set the light position
	pos[0] = position.x;
	pos[1] = position.y;
	pos[2] = position.z;
	pos[3] = !directional;

	//Set the light colour values

	amb[0] = ambient.r;
	amb[1] = ambient.g;
	amb[2] = ambient.b;
	amb[3] = ambient.a;

	dif[0] = diffuse.x;
	dif[1] = diffuse.y;
	dif[2] = diffuse.z;
	dif[3] = 1;

	spec[0] = specular.r;
	spec[1] = specular.g;
	spec[2] = specular.b;
	spec[3] = specular.a;
}


Light::~Light()
{
}

void Light::DebugRender()
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
	glVertex3f(-1, 1, 1); // FTL
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
