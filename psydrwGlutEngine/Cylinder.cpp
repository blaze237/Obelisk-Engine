#include "Cylinder.h"



Cylinder::Cylinder(Vec3<float> pos, std::string tag, Texture2D tex)
	:DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), texture(tex)
{
}

Cylinder::Cylinder(Vec3<float> pos, std::string tag, Texture2D tex, float texTiling)
	: DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), texture(tex), texTilingX(texTiling), texTilingZ(texTiling)
{
}

Cylinder::Cylinder(Vec3<float> pos, std::string tag, Texture2D tex, float texTilingX, float texTilingZ)
	: DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), texture(tex), texTilingX(texTilingX), texTilingZ(texTilingZ)
{
}


Cylinder::~Cylinder()
{
}

void Cylinder::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.getID());

	//Going to loop around the rim of cyldiner of height 1, radius 0.5 and angular some resolution
	float res = 0.05*M_PI;         
	float x = 0.5;
	float z = 0.f;         
	float theta = 2 * M_PI;             

	while (theta > 0)
	{
		//Precalc the next point around the circle as we need it to calculate the normals
		float xNext = 0.5 * cos(theta -  res);
		float zNext = 0.5 * sin(theta - res);


		//Draw a vertical section of the cylinder
		glBegin(GL_QUADS);        

		//To get normal, get normal of the plane representing this section/face
		Vec3<float> A(xNext, 0.f, zNext);
		Vec3<float> B(x, 0.f, z);
		Vec3<float> C(x, 1, z);
		Vec3<float> normal = (B - A).CrossProd(C - A);
		normal.Normalise();
			
		glNormal3f(normal.x, normal.y, normal.z);


		//Top and bottom of first part of this section
		glTexCoord2f((theta / (2.0 * M_PI)) * texTilingX, 1 * texTilingZ);
		glVertex3f(x, 1, z);    
		glTexCoord2f((theta / (2.0 * M_PI)) * texTilingX, 0);
		glVertex3f(x, 0.f, z);  
		
		//Move around the circle		
		theta -= res;
		x = xNext;
		z = zNext;

		//Bottom and top of second half of this section
		glTexCoord2f((theta / (2.0 * M_PI)) * texTilingX, 0);
		glVertex3f(x, 0.f, z); 
		glTexCoord2f((theta / (2.0 * M_PI)) * texTilingX, 1 * texTilingZ);
		glVertex3f(x, 1, z);   

		glEnd();                    
	}

	// Bind to blank buffer 
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}
