#include "FPSCamera.h"
#include "SceneManager.h"
#include <iostream>

//#define DEBUG

FPSCamera::FPSCamera(Vec3<float> eyePos, Vec3<float> viewDir)
	:Camera(eyePos, viewDir), mousePos(SceneManager::GetScreenW() / 2, SceneManager::GetScreenH() / 2)
{
}


FPSCamera::~FPSCamera()
{
}

void FPSCamera::Update(long tCurrent)
{
	if (!InputManager::IsDown(InputManager::CTRL)) 
	{
		//Handle keyboard input
		CheckMovement();

		//Handle mouse input
		CheckRotation();

		//Move cursor back to center, without this mouse is able to leave the window
		glutWarpPointer(SceneManager::GetScreenW() / 2, SceneManager::GetScreenH() / 2);
		mousePos.x = SceneManager::GetScreenW() / 2;
		mousePos.y = SceneManager::GetScreenH() / 2;

		//Set the view in opengl
		SetCamMatrix();

	#ifdef DEBUG
			std::cout << "Eye" << eyePos.x << "," << eyePos.y << "," << eyePos.z << std::endl;
			std::cout << "View" << viewDir.x << "," << viewDir.y << "," << viewDir.z << std::endl;
			std::cout << std::endl;
	#endif
	}
}

void FPSCamera::CheckMovement()
{
	if (InputManager::IsDown(inputL))
		eyePos -= u * speed;
	if (InputManager::IsDown(inputU))
		eyePos += n * speed;
	if (InputManager::IsDown(inputR))
		eyePos += u * speed;
	if (InputManager::IsDown(inputD))
		eyePos -= n * speed;
}

void FPSCamera::CheckRotation()
{
	//Get change in mouse position
	Vec2<int> newPos = InputManager::GetMousePos();
	int dx = (float)(mousePos.x - newPos.x);
	int dy = (float)(mousePos.y - newPos.y);

	//if(dx)
	//Use change in position to alter the view direction of the camera
	viewDir -= u * (sensitivity * dx);
	viewDir += v * (sensitivity * dy);

	//Normalise view direction to be unit vector
	viewDir.Normalise();

	//Obtain new u co-ord direction as cross product of v and viewDir
	u = viewDir.CrossProd(v);

	//Normalise u co-ord
	u.Normalise();

	//Obtain our new forward (n) co-ord. No need to normalise as allready done this to view dir
	n = viewDir;
}
