#pragma once
#include "Vec3.h"
#include <GL/glut.h>
#include "InputManager.h"
#include "Plane.h"
#include "MathHelp.h"
class Camera
{
public:
	Camera(Vec3<float> eyePos, Vec3<float> viewDir);
	virtual ~Camera();

	inline void HandleReshape(int w, int h)
	{
		// calculate new aspect ratio
		GLdouble aspect = static_cast<GLdouble>(w) / static_cast<GLdouble>(h);

		glMatrixMode(GL_PROJECTION);
		// reset matrix
		glLoadIdentity();

		// Set the viewport to be the entire window
		glViewport(0, 0, w, h);

		gluPerspective(FOV, aspect, nearDist, farDist);
		// return matrix mode to modelling and viewing
		glMatrixMode(GL_MODELVIEW);

		//Update stored frustum info
		RecalcFrustumParams(aspect);
	}

	inline Vec3<float> GetEyePos() const
	{
		return eyePos;
	}
	inline Vec3<float> GetViewDir() const
	{
		return viewDir;
	}
	inline Vec3<float> GetU() const
	{
		return u;
	}
	inline Vec3<float> GetV() const
	{
		return v;
	}
	inline Vec3<float> GetN() const
	{
		return n;
	}
	inline float GetNearDist() const
	{
		return nearDist;
	}
	inline float GetFarDist() const
	{
		return farDist;
	}
	inline float GetFOV() const
	{
		return FOV;
	}
	virtual inline void SetEyePos(Vec3<float> v)
	{
		eyePos = v;
	}
	inline void SetViewDir(Vec3<float> v)
	{
		viewDir = v;
	}
	inline void SetFOV(float fov) {
		FOV = fov;
	}


	std::vector<Plane> GetFrustum();

	//Apply camera paramters to opengl matrix statck. Call after any changes to cam pos
	virtual void SetCamMatrix() const;

	//Overload to handle input etc. 
	virtual void Update(long tCurrent);
	//Can overload to provide easy way of resetting camera pos etc. 
	virtual void Reset();


protected:

	inline void RecalcFrustumParams(float r)
	{
		ratio = r;

		hNear = 2 * tan(MathHelp::ToRadians<float>(FOV / 2.f)) * nearDist/2;
		wNear = hNear * ratio;

		hFar = 2 * tan(MathHelp::ToRadians<float>(FOV/2.f)) * farDist/2;
		wFar = hFar * ratio;
	}

	//Position of the camera
	Vec3<float> eyePos;



	//Frustrum paramaters
	float FOV = 45;
	float hNear, wNear, hFar, wFar, ratio;
	float farDist = 1300;
	float nearDist = 1;
	//Position in space the camera is looking at
	Vec3<float> viewDir;

	//Viewspace coordiantes
	 Vec3<float> u;
	 Vec3<float> v;
	 Vec3<float> n;
};

