#include "Torch.h"


Torch::Torch(Vec3<float> pos, Texture2D handleTex, Texture2D sprites, std::string tag, Camera& cam, int nFrames, float frameWidth, long frameRate, Vec3<float> orientation, Vec3<float> flameOffset)
	:AllignedSprite(pos, sprites, tag, cam, nFrames, frameWidth, frameRate), handleTex(handleTex), bBoxCust(bBox.width, bBox.height *3, bBox.depth, this->pos, orientation, this->scale), fOffsetX(flameOffset.x), fOffsetY(flameOffset.y), fOffsetZ(flameOffset.z)
{
	this->orientation = orientation;
	cullBackFaces = false;
}

Torch::Torch(Vec3<float> pos, Texture2D handleTex, Texture2D sprites, std::string tag, Camera& cam, int nFrames, float frameWidth, long frameRate, Vec3<float> orientation, float handleTexTiling, Vec3<float> flameOffset)
	: AllignedSprite(pos, sprites, tag, cam, nFrames, frameWidth, frameRate), handleTex(handleTex), handleTexTilingX(handleTexTiling), handleTexTilingZ(handleTexTiling), bBoxCust(bBox.width, bBox.height * 3 , bBox.depth, this->pos, this->orientation = orientation , this->scale),
	fOffsetX(flameOffset.x), fOffsetY(flameOffset.y), fOffsetZ(flameOffset.z)
{
	this->orientation = orientation;
	cullBackFaces = false;
}

Torch::Torch(Vec3<float> pos, Texture2D handleTex, Texture2D sprites, std::string tag, Camera& cam, int nFrames, float frameWidth, long frameRate, Vec3<float> orientation, float handleTexTilingX, float handleTexTilingZ, Vec3<float> flameOffset)
	: AllignedSprite(pos, sprites, tag, cam, nFrames, frameWidth, frameRate), handleTex(handleTex), handleTexTilingX(handleTexTilingX), handleTexTilingZ(handleTexTilingZ),  bBoxCust(bBox.width, bBox.height * 2, bBox.depth, this->pos, this->orientation = orientation, this->scale),
	fOffsetX(flameOffset.x), fOffsetY(flameOffset.y), fOffsetZ(flameOffset.z)
{
	this->orientation = orientation;
	cullBackFaces = false;
}

Torch::~Torch()
{
}

void Torch::Render()
{
	glDisable(GL_LIGHTING);

	//Handle transforms ourselves for this object to make orientating the flame sprite upright easier
	glPopMatrix();
	
	//Have to use a custom bbox that isnt subject to the y-rotation caused by the sprite component
	if(renderCollider)
		bBoxCust.Render();


	glPushMatrix();

	//Move drawing to object location
	glTranslatef(pos.x, pos.y, pos.z);
	//Apply rotation. Torch body can only be rotated in z or x
	glRotatef(orientation.z, 0, 0, 1);
	glRotatef(orientation.x, 1, 0, 0);
	//Set drawing scale
	glScalef(scale.x, scale.y, scale.z);
	//Draw handle of the torch
	DrawHandle();

	glPopMatrix();
	glPushMatrix();

	//Move drawing to object location again
	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(scale.x, scale.y, scale.z);

	//Apply rotation of the handle, then move to the tip of the handle
	glRotatef(orientation.z, 0, 0, 1);
	glRotatef(orientation.x, 1, 0, 0);
	glTranslatef(fOffsetX, fOffsetY, fOffsetZ);
	glRotatef(-orientation.x, 1, 0, 0);
	glRotatef(-orientation.z, 0, 0, 1);
	//Then, we want to rotate to -90 in worldspace
	glRotatef(-90, 1, 0, 0);
	//Then apply the y rotation of the sprite
	glRotatef(orientation.y, 0, 0, 1);

	//Finaly we apply a scale boost for the sprite to ensure it fills the handle
	glScalef(2, 2, 2);
	
	//The sprites true orientation in x/z is -90 degrees, even if the orientation of the torch object is not this. Hence we temporaily set the value of the x orienation to be this to allow for proper calculation of sprite normals.
	float tmp = orientation.x;
	orientation.x = -90;

	//Draw the sprite 
	AllignedSprite::Render();

	//Restore the orientation
	orientation.x = tmp;

	glEnable(GL_LIGHTING);

}

void Torch::DrawHandle()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, handleTex.getID());

	//Going to loop around the rim (at one end and pinch other) of cyldiner of height 1, radius 0.5 and angular some resolution 
	float res = resolution * M_PI;
	float x = 0.5;
	float z = 0.f;
	float theta = 2 * M_PI;

	while (theta > 0)
	{
		//Precalc the next point around the circle as we need it to calculate the normals
		float xNext = 0.5 * cos(theta - res);
		float zNext = 0.5 * sin(theta - res);


		//Draw a vertical section of the cylinder
		glBegin(GL_QUADS);

		glNormal3f(x, 0, z);
		//Top and bottom of first part of this section
		glTexCoord2f((theta / (2.0 * M_PI)) * handleTexTilingX, 1 * handleTexTilingZ);
		glVertex3f(x, 0.5, z);
		glTexCoord2f((theta / (2.0 * M_PI)) * handleTexTilingX, 0);
		glVertex3f(0, -0.5, 0);

		//Move around the circle		
		theta -= res;
		x = xNext;
		z = zNext;
		glNormal3f(x, 0, z);

		//Bottom and top of second half of this section
		glTexCoord2f((theta / (2.0 * M_PI)) * handleTexTilingX, 0);
		glVertex3f(0, -0.5, 0);
		glTexCoord2f((theta / (2.0 * M_PI)) * handleTexTilingX, 1 * handleTexTilingZ);
		glVertex3f(x, 0.5, z);

		glEnd();
	}

	// Bind to blank buffer 
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}