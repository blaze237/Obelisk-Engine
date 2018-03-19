#pragma once
#include "Vec3.h"
#include <GL/glut.h>
#include "InputManager.h"

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

		gluPerspective(45.0, aspect, nearClip, farClip);
		// return matrix mode to modelling and viewing
		glMatrixMode(GL_MODELVIEW);
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
	inline float GetNearClip()
	{
		return nearClip;
	}
	inline float GetFarClip()
	{
		return farClip;
	}
	inline void setEyePos(Vec3<float> v) {
		eyePos = v;
	}


	//Apply camera paramters to opengl matrix statck. Call after any changes to cam pos
	virtual void SetCamMatrix() const;

	//Overload to handle input etc. Default uses FPS controll scheme
	virtual void Update(long tCurrent);
	//Can overload to provide easy way of resetting camera pos etc. 
	virtual void Reset();


protected:
	//Position of the camera
	Vec3<float> eyePos;

	float farClip = 2000;
	float nearClip = 1;

	//Position in space the camera is looking at
	Vec3<float> viewDir;

	//Viewspace coordiantes
	 Vec3<float> u;
	 Vec3<float> v;
	 Vec3<float> n;
};

