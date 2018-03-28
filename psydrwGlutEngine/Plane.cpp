#include "Plane.h"
#include <iostream>



Plane::Plane(Vec3<float> pos, Texture2D texture, std::string tag, int resolution)
	:DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag, texture), resolution(resolution)
{
	renderCollider = true;
}

Plane::Plane(Vec3<float> pos, Texture2D texture, std::string tag, int resolution, float texTiling)
	: DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag, texture), resolution(resolution), texTiling(texTiling)
{
	renderCollider = true;
}


Plane::~Plane()
{
}

void Plane::Render()
{

	glBegin(GL_QUADS);
	float step = 1.0f / resolution;
	for (int x = -resolution/2; x < resolution/2; ++x)
	{
		for (int z = -resolution/2; z < resolution/2; ++z)
		{

			//1
			glNormal3f(0, 1, 0);
			glTexCoord2f(((x + resolution/2) * step)* texTiling, ((z + resolution /2) * step + step)* texTiling);
			glVertex3f(x * step, 0, z * step + step);
			//2
			glTexCoord2f(((x + resolution / 2)* step + step)* texTiling, ((z + resolution / 2) * step + step)* texTiling);
			glVertex3f(x * step + step, 0, z * step + step);
			//3
			glTexCoord2f(((x + resolution / 2) * step + step)* texTiling, ((z + resolution / 2) * step)* texTiling);
			glVertex3f(x * step + step, 0,  z* step);
			//4
			glTexCoord2f(((x + resolution / 2) * step)* texTiling, ((z + resolution / 2) * step)* texTiling);
			glVertex3f(x * step, 0, z * step);
			

		

		}
	}

	glEnd();
}
