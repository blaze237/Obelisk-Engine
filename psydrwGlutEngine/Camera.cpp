#include "Camera.h"



Camera::Camera()
	:u(1.0f,0.0f,0.0f), v(0.0f, 1.0f, 0.0f), n(0.0f, 0.0f, -1.0f), viewDir(0.0f, 0.0f, -1.0f), eyePos(0.0f, 0.0f, 0.0f)
{
}


Camera::~Camera()
{
}

void Camera::SetCamMatrix() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyePos.x, eyePos.y, eyePos.z, eyePos.x + viewDir.x, eyePos.y + viewDir.y, eyePos.z + viewDir.z, v.x, v.y, v.z);
}

void Camera::Update(long tCurrent)
{
	//Handle keyboard input
	if(InputManager::IsDown(inputL))
		eyePos -= u * speed;
	if(InputManager::IsDown(inputU))
		eyePos += n * speed;
	if(InputManager::IsDown(inputR))
		eyePos += u * speed;
	if (InputManager::IsDown(inputD))
		eyePos -= n * speed;

	//Handle mouse input


	//Get change in mouse position
	Vec2<int> newPos = InputManager::GetMousePos();
	int dx = (float)(mousePos.x - newPos.x);
	int dy = (float)(mousePos.y - newPos.y);

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

	SetCamMatrix();


	glutWarpPointer(400, 400);
	mousePos.x = 400;
	mousePos.y = 400;

}

void Camera::Reset()
{
}
