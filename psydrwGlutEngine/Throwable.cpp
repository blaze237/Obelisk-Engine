#include "Throwable.h"



Throwable::Throwable(Vec3<float> pos, Texture2D tex)
	:DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), "THROWABLE"), texture(tex)
{
	//bBox.SetTrigger(true);

	//Trowable will sleep until it is needed
	Deactivate();
}


Throwable::~Throwable()
{
}

void Throwable::Render()
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

void Throwable::OnTrigger(std::string tag)
{
	if (!tag.compare("TARGET"))
		Deactivate();
	

}

bool Throwable::OnCollide(std::string tag)
{
	//We dont want the throwable to collide with the player
	if (!tag.compare("Cam"))
		return true;
	else if (!tag.compare("TARGET"))
	{
		std::cout << "HI";
		Deactivate();

	}
	return false;
}

void Throwable::Update(long tCurrent)
{

}

void Throwable::Activate(Vec3<float> vel, Vec3<float> position)
{
	collidable = true;
	renderable = true;
	kinematic = true;

	velocity = vel;
	pos = position;
}

void Throwable::Deactivate()
{
	collidable = false;
	renderable = false;
	kinematic = false;
	velocity = Vec3<float>(0, 0, 0);
}
