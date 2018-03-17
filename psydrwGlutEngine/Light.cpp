#include "Light.h"



Light::Light(Vec3<float>position, Colour ambient, Colour diffuse, Colour specular, bool directional)
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

	dif[0] = diffuse.r;
	dif[1] = diffuse.g;
	dif[2] = diffuse.b;
	dif[3] = diffuse.a;

	spec[0] = specular.r;
	spec[1] = specular.g;
	spec[2] = specular.b;
	spec[3] = specular.a;
}


Light::~Light()
{
}
