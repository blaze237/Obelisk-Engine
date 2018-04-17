#pragma once
#include "DisplayableObject.h"
#include "Camera.h"
#include "Texture2D.h"
#include "BoxFace.h"
class AllignedSprite :
	public DisplayableObject
{
public:
	AllignedSprite(Vec3<float> pos, Texture2D tex, std::string tags, Camera& cam, int nFrames, float frameWidth, long frameRate);
	virtual ~AllignedSprite();

	virtual void Update(long tCurrent);
	virtual void Render();

private:
	//Allign the normal of the sprite to be antiparralel to camera view dir
	void AllignToCam();
	//Get the current normal of the sprite
	Vec2<float> CalcNormal();
	Camera& cam;
	Texture2D sprites;

	//How many frames are there in the spritesheet
	int nFrames;
	//How wide is each frame in pixels
	float frameWidth;
	//Used to store the current relative position in the spritesheet of the current frame
	float frameXStart = 0;
	float frameXEnd;
	int curFrame = 0;
	//Keep track of how much time has passed since last frame update
	long tSinceUpdate = 0;
	long lastTime = 0;
	//How long to wait between frame updates
	long frameRate;

};

