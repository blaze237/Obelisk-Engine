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


std::vector<Plane> Camera::GetFrustum()
{
	//First we define the co-ordinate system of the frustum
	Vec3<float> X, Y, Z;
	Z = viewDir * -1;
	Z.Normalise();
	X = v.CrossProd(Z);
	X.Normalise();
	Y = Z.CrossProd(X);
	Y.Normalise();

	// compute the centers of the near and far planes
	Vec3<float> nc = eyePos - Z * nearDist/2;
	Vec3<float> fc = eyePos - Z * farDist/2;


	std::vector<Plane> planes;

	//Near plane
	planes.push_back(Plane(nc, Z*-1));
	//Far
	planes.push_back(Plane(fc, Z));


	//Use these to calculate the 4 remaining planes as cross products with each axis
	Vec3<float> tmp, normal;

	//Top
	tmp = (nc + Y * hNear/2) - eyePos;
	tmp.Normalise();
	normal = tmp.CrossProd(X);
	planes.push_back(Plane(eyePos, normal));


	//Bottom
	tmp = (nc - Y * hNear/2) - eyePos;
	tmp.Normalise();
	normal = X.CrossProd(tmp);
	planes.push_back(Plane(eyePos, normal));

	//Left
	tmp = (nc - X * wNear/2) - eyePos;
	tmp.Normalise();
	normal = tmp.CrossProd(Y);
	planes.push_back(Plane(eyePos, normal));

	//Right
	tmp = (nc + X * wNear/2) - eyePos;
	tmp.Normalise();
	normal = Y.CrossProd(tmp);
	planes.push_back(Plane(eyePos, normal));

	return planes;
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
