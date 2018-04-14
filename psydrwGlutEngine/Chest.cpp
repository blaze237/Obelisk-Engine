#include "Chest.h"
#include "SceneManager.h"

Chest::Chest(Vec3<float> pos, std::string tag, Texture2D texture, float texTilingX, float texTilingZ)
	: DisplayableObject(pos, Vec3<float>(0.75, 1, 2.6), tag), texture(texture), texTilingX(texTilingX), texTilingZ(texTilingZ)
{
}

Chest::~Chest()
{
}


void Chest::Render()
{
	if(playAnim)
		SceneManager::DrawScreenString("CONGRATULATIONS!", Vec2<int>(SceneManager::GetScreenW() / 2 - (SceneManager::GetScreenW() / 20), SceneManager::GetScreenH() / 2), Colour(1, 0, 0, 1));


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.getID());

	DrawBase();

	//Move drawing to object location
	glTranslatef(0, (0.5*scale.y + 0.5 * LidThickness * scale.y) / scale.y, 0);

	//Translate to the back center
	glTranslatef(0, -0.1, 0.5);
	glRotatef(LidAngle, 1, 0, 0);
	glTranslatef(0, 0.1, -0.5);

	glScalef(1, LidThickness, 1);

	DrawLid();

	// Bind to blank buffer 
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}

void Chest::OnTrigger(std::string tag)
{
	if(!playAnim && LidAngle != LID_ANGLE_MAX)
		playAnim = true;
}

void Chest::Update(long tCurrent)
{
	long dt = tCurrent - prevtime;
	if (playAnim && dt >= ANIM_RATE)
	{
		if (LidAngle < LID_ANGLE_MAX)
			LidAngle++;
		
		else
			playAnim = false;
	}
	

	prevtime = tCurrent;
}

void Chest::DrawBase()
{
	
	glBegin(GL_QUADS);
	//Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, 0.5f);

	//Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	//Left face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	//Right Face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, -0.5f);

	//Top face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.5f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.5f, 0.0f);
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
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glEnd();
}

void Chest::DrawLid()
{
	glBegin(GL_QUADS);

	//Front Face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, 0.5f);

	//Back Face
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	//Left face
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	//Right Face
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, -0.5f);

	//Top face
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, 0.5f, -0.5f);

	//Bottom Face
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f * texTilingZ);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.5f * texTilingX, 1.0f * texTilingZ);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glEnd();
}
