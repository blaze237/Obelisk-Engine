#include "SkyBox.h"
#include <iostream>
#include "SceneManager.h"



SkyBox::SkyBox(const std::vector<Texture2D>& texts)
	:textures(texts)
{
	//Give warning if excess texture data was passed. Wont actualy affect rendering but user may wish to know 
	if (textures.size() > 6)
		std::cout << "Number of textures exceeds number of faces (6)!" << std::endl;

	//If not enough texture, tell the user and insert blank placeholder textures to use to avoid crashing
	if (textures.size() < 6)
	{
		std::cout << "Insufficient number of textures supplied to skybox!" << std::endl;

		while (textures.size() < 6)
			textures.push_back(SceneManager::GetErrorTexture());
	}
}

SkyBox::~SkyBox()
{
}

void SkyBox::Render()
{
	glPushMatrix();
	
	//Set drawing scale
	glScalef(scale.x, scale.y, scale.z);
	//glScalef(50, 50, 50);
	//Disable lighting for skybox
	glDisable(GL_LIGHTING);
	//Enable Texturing
	glEnable(GL_TEXTURE_2D);

	glColor4f(1.f, 1.f, 1.f, 1.f);          // Set fill to be invisible (only texture is rendered)


	//Left Face
	glBindTexture(GL_TEXTURE_2D, textures[0].getID());
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(-1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 1.f); 
	glVertex3f(-1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(-1.f, 0.f, 1.f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();

	//Right Face
	glBindTexture(GL_TEXTURE_2D, textures[1].getID());
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f); 
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 1.f); 
	glVertex3f(1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 0.f);  
	glVertex3f(1.f, 0.f, -1.f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(1.f, 0.f, 1.f);
	glEnd();

	//Back Face
	glBindTexture(GL_TEXTURE_2D, textures[2].getID());
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);  
	glVertex3f(1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 1.f); 
	glVertex3f(-1.f, 1.f, -1.f);
	glTexCoord2f(0.f, 0.f); 
	glVertex3f(-1.f, 0.f, -1.f);
	glTexCoord2f(1.f, 0.f); 
	glVertex3f(1.f, 0.f, -1.f);
	glEnd();

	//Front Face
	glBindTexture(GL_TEXTURE_2D, textures[3].getID());
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);  
	glVertex3f(-1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 1.f); 
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 0.f);  
	glVertex3f(1.f, 0.f, 1.f);
	glTexCoord2f(1.f, 0.f); 
	glVertex3f(-1.f, 0.f, 1.f);
	glEnd();

	//Bottom Face
	glBindTexture(GL_TEXTURE_2D, textures[4].getID());
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);  
	glVertex3f(-1.f, 0.f, 1.f);
	glTexCoord2f(1.f, 0.f); 
	glVertex3f(1.f, 0.f, 1.f);
	glTexCoord2f(1.f, 1.f);  
	glVertex3f(1.f, 0.f, -1.f);
	glTexCoord2f(0.f, 1.f); 
	glVertex3f(-1.f, 0.f, -1.f);
	glEnd();

	//Top Face
	glBindTexture(GL_TEXTURE_2D, textures[5].getID());
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f); 
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 1.f); 
	glVertex3f(-1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 0.f); 
	glVertex3f(-1.f, 1.f, -1.f);
	glTexCoord2f(1.f, 0.f);  
	glVertex3f(1.f, 1.f, -1.f);
	glEnd();


	glDisable(GL_TEXTURE_2D);   
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
