#pragma once
#include "Vec3.h"
#include <GL/glut.h>
#include "InputManager.h"

class Camera
{
public:
	Camera(Vec3<float> eyePos, Vec3<float> viewDir);
	~Camera();


	inline const Vec3<float>& GetEyePos() const
	{
		return eyePos;
	}
	inline const Vec3<float>& GetViewDir() const
	{
		return viewDir;
	}
	inline const Vec3<float>& GetU() const
	{
		return u;
	}
	inline const Vec3<float>& GetV() const
	{
		return v;
	}
	inline const Vec3<float>& GetNr() const
	{
		return n;
	}


	void setEyePos(Vec3<float> v) {
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

	//Position in space the camera is looking at
	Vec3<float> viewDir;

	//Viewspace coordiantes
	 Vec3<float> u;
	 Vec3<float> v;
	 Vec3<float> n;

};

