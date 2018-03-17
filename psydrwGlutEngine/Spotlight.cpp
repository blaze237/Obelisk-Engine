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
