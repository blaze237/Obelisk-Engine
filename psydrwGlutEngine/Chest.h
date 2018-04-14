#pragma once
#include "DisplayableObject.h"
class Chest :
	public DisplayableObject
{
	const float LID_ANGLE_MAX = 70;
	const long ANIM_RATE = 2;

public:
	Chest(Vec3<float> pos, std::string tag, Texture2D texture, float texTilingX, float texTilingZ);
	virtual ~Chest();

	virtual void Render();
	virtual void OnTrigger(std::string tag);
	virtual void Update(long tCurrent);
private:

	
	void DrawBase();
	void DrawLid();

	//Flag to signal when to start animating lid opening 
	bool playAnim = false;
	//Used for tracking animation time
	long prevtime;
	Texture2D texture;
	float texTilingX = 1;
	float texTilingZ = 1;
	float LidAngle = 0;
	float LidThickness = 0.2;
};

