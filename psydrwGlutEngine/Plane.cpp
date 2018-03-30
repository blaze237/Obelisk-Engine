#include "Plane.h"
#include <iostream>



Plane::Plane(Vec3<float> pos, Texture2D texture, std::string tag, int resolution)
	:DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), resolution(resolution), texture(texture)
{
}

Plane::Plane(Vec3<float> pos, Texture2D texture, std::string tag, int resolution, float texTiling)
	: DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), resolution(resolution), texTiling(texTiling), texture(texture)
{
}


Plane::~Plane()
{
}

void Plane::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.getID());

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

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}
