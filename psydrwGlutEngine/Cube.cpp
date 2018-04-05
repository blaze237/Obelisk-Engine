#include "Cube.h"



Cube::Cube(Vec3<float> pos, std::string tag, Texture2D texture)
	:DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), texture(texture)
{
}

Cube::Cube(Vec3<float> pos, std::string tag, Texture2D texture, float texTiling)
	: DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), texture(texture), texTilingX(texTiling), texTilingZ(texTiling)

{
}

Cube::Cube(Vec3<float> pos, std::string tag, Texture2D texture, float texTilingX, float texTilingZ)
	: DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), texture(texture), texTilingX(texTilingX), texTilingZ(texTilingZ)

{
}


Cube::~Cube()
{
}

void Cube::Render()
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
	glBegin(GL_QUADS);

	//Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f * texTilingX, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, 0.5f);

	//Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f * texTilingX, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	//Left face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f * texTilingX, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	//Right Face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f * texTilingX, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, -0.5f);

	//Top face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f * texTilingX, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, -0.5f);

	//Bottom Face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f * texTilingX, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glEnd();

	// Bind to blank buffer 
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}
