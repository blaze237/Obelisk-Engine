#include "Sphere.h"


Sphere::Sphere(Vec3<float> pos, std::string tag, Texture2D texture)
	:DisplayableObject(pos, Vec3<float>(1, 1, 1), tag), texture(texture)
{
}


Sphere::~Sphere()
{
}


void Sphere::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
	
	//We are going to define a sphere using its parametric equation by stepping over lines of latitude and longitude
	float latStep = 2 * PI / resolution;
	float longStep = PI / resolution;
	

	for (int i = 0; i < resolution; ++i)
	{
		for (int j = 0; j < resolution; ++j)
		{
			//Get angles of lat and long for the two corners of this grid section
			float phi = i * latStep;
			float theta = j * longStep;
			float phiNext = MathHelp::Clamp((i + 1) * latStep, 0.f, (float)(2 * PI));
			float thetaNext = MathHelp::Clamp((j + 1) * longStep, 0.f, (float)PI);

			//Determine the four corners of this grid section using the spheres parametric equation
			Vec3<float> a = SphericalToCartesian(phi, theta);
			Vec3<float> b = SphericalToCartesian(phi, thetaNext);
			Vec3<float> c = SphericalToCartesian(phiNext, theta);
			Vec3<float> d = SphericalToCartesian(phiNext, thetaNext);

			//Plot the verticies
			glBegin(GL_TRIANGLES);

			//Triangle 1
			glTexCoord2f((phi / (2 * PI)) * texTilingX, (theta / PI) * texTilingZ);
			glNormal3f(a.x, a.y, a.z);
			glVertex3f(a.x, a.y, a.z);

			glTexCoord2f((phiNext / (2 * PI)) * texTilingX, (theta / PI) * texTilingZ);
			glNormal3f(c.x, c.y, c.z);
			glVertex3f(c.x, c.y, c.z);

			glTexCoord2f((phi / (2 * PI)) * texTilingX, (thetaNext / PI) * texTilingZ);
			glNormal3f(b.x, b.y, b.z);
			glVertex3f(b.x, b.y, b.z);

			//Triangle 2
			glTexCoord2f((phiNext / (2 * PI)) * texTilingX, (thetaNext / PI) * texTilingZ);
			glNormal3f(d.x, d.y, d.z);
			glVertex3f(d.x, d.y, d.z);

			glTexCoord2f((phi / (2 * PI)) * texTilingX, (thetaNext / PI) * texTilingZ);
			glNormal3f(b.x, b.y, b.z);
			glVertex3f(b.x, b.y, b.z);

			glTexCoord2f((phiNext / (2 * PI)) * texTilingX, (theta / PI) * texTilingZ);
			glNormal3f(c.x, c.y, c.z);
			glVertex3f(c.x, c.y, c.z);

			glEnd();

		}
	}

	// Bind to blank buffer 
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}


