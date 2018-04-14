#pragma once
#include "Camera.h"

class FPSCamera : public Camera
{
public:
	FPSCamera(Vec3<float> eyePos, Vec3<float> viewDir);
	~FPSCamera();


	//Update cam pos based on user input
	virtual void Update(long tCurrent);


protected:
	//Check for and apply movement input
	virtual void CheckMovement();
	//Check for and apply rotation (mouse) input
	void CheckRotation();
	//Keep the mouse in the centre of the screen;
	void WarpPointer();
	char inputL = 'a';
	char inputU = 'w';
	char inputR = 'd';
	char inputD = 's';
	Vec2<int> mousePos;
	const float sensitivity = 0.003f;
private:
	const float speed = 1;
	
};

