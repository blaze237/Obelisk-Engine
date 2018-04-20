#include "Spotlight.h"
#include <cstdio>
#include <iostream>

Spotlight::Spotlight(Vec3<float>pos, Colour ambient, Vec3<int> diffuse, Colour specular, Vec3<float> direction)
	:Light(pos, ambient, diffuse, specular, false)
{
	dir[0] = direction.x;
	dir[1] = direction.y;
	dir[2] = direction.z;
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
	//Set light cone paramaters
	glLightf(lightID, GL_SPOT_CUTOFF, cuttOff);
	glLightf(lightID, GL_SPOT_EXPONENT, exponent);
	//Set direction
	glLightfv(lightID, GL_SPOT_DIRECTION, dir);
	//Set the attenuation values
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1.f / (2.f * radius));
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 1.0f / (2.f * radius * radius));

	glEnable(lightID);

}

