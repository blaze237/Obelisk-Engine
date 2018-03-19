#include "Camera.h"
#include <iostream>
#include "SceneManager.h"

Camera::Camera(Vec3<float> eyePos, Vec3<float> viewDir)
	:u(1.0f,0.0f,0.0f), v(0.0f, 1.0f, 0.0f), n(0.0f, 0.0f, -1.0f), viewDir(viewDir), eyePos(eyePos)
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

}

void Camera::Reset()
{
}
