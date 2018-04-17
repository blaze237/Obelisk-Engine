#include "AllignedSprite.h"



AllignedSprite::AllignedSprite(Vec3<float> pos, Texture2D tex, std::string tag, Camera& cam, int nFrames, float frameWidth, long frameRate)
	:DisplayableObject(pos, Vec3<float>(0.5, 0.5, 0.5), tag), sprites(tex), cam(cam), nFrames(nFrames), frameWidth(frameWidth), frameRate(frameRate), frameXEnd(frameWidth)
{
}


AllignedSprite::~AllignedSprite()
{
}

void AllignedSprite::Update(long tCurrent)
{
	tSinceUpdate += (tCurrent - lastTime);
	lastTime = tCurrent;

	//Do nothing if not enough time passed yet
	if (tSinceUpdate < frameRate)
		return;

	//Otherwise, advance to next frame of animation
	tSinceUpdate = 0;
	curFrame = curFrame == nFrames-1 ? 0 : curFrame + 1;

	//Get new texture co-ords for current frame
	frameXStart = ((float)curFrame * frameWidth) / (nFrames * frameWidth);
	frameXEnd = ((float)(curFrame + 1) * frameWidth) / (nFrames * frameWidth);



}

void AllignedSprite::Render()
{
	//Get sprite facing in the right direction
	AllignToCam();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sprites.getID());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);


	glNormal3f(0, 1, 0);
	//Top left
	glTexCoord2f(frameXStart, 1);
	glVertex3f(-0.5, 0, 0.5);
	//Bot left
	glTexCoord2f(frameXStart, 0);
	glVertex3f(-0.5, 0, -0.5);
	//Bot right
	glTexCoord2f(frameXEnd, 0);
	glVertex3f(0.5, 0, -0.5);
	//Top right
	glTexCoord2f(frameXEnd, 1);
	glVertex3f(0.5, 0, 0.5);


	glEnd();

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}



void AllignedSprite::AllignToCam()
{
	//Get camera viewing direction. We want to allign with the opposite of it
	Vec3<float> camNorm3d = cam.GetViewDir() * -1;
	//We only care about the component of the normal within the x-z plane, so just extract those parts
	Vec2<float> camNorm(camNorm3d.x, camNorm3d.z);
	camNorm.Normalise();

	//Get the sprites current normal in world space
	Vec2<float> curNorm = CalcNormal();

	//If allready alligned, do nothing
	if (camNorm == curNorm)
		return;

	//Use the dot product and determinent to get the sine and cosine of angle in y between our current normal and desired one (-ve cam view dir)
	float dot = curNorm.DotProd(camNorm);
	float det = curNorm.Det(camNorm);
	//Get the angle
	float angle = MathHelp::ToDegrees(atan2(det, dot));
	//Rotate by this angle to align the normal
	orientation.y -= angle;
}

Vec2<float> AllignedSprite::CalcNormal()
{
	//We need to get the world space co-ordinates of three of the planes verticies (in counter clockwise order). 

	//Top left
	Vec3<float> A = Vec3<float>(-0.5, 0, 0.5);
	//Bot Right 
	Vec3<float> B = Vec3<float>(0.5, 0, -0.5);
	//Top Right
	Vec3<float> C = Vec3<float>(0.5, 0, 0.5);


	//Apply the sprites rotation so points are alligned correctly in local space
	A = MathHelp::RotatePoint(A, orientation);
	B = MathHelp::RotatePoint(B, orientation);
	C = MathHelp::RotatePoint(C, orientation);

	//Apply sprite translation to get points in correct position in world space
	A = A + pos;
	B = B + pos;
	C = C + pos;

	Vec3<float> norm = (B - A).CrossProd(C - A);
	norm.Normalise();
	//We only care about the component of the normal within the x-z plane, so just extract those parts
	Vec2<float> norm2D(norm.x, norm.z);
	norm2D.Normalise();
	
	return norm2D;
}

