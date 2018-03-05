#pragma once
#include "Vec3.h"
#include <GL/glut.h>
#include "InputManager.h"

class Camera
{
public:
	Camera();
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
	inline const Vec3<float> GetNr() const
	{
		return n;
	}

	//Apply camera paramters to opengl matrix statck. Call after any changes to cam pos
	virtual void SetCamMatrix() const;

	//Overload to handle input etc. Default uses FPS controll scheme
	virtual void Update(long tCurrent);
	//Can overload to provide easy way of resetting camera pos etc. Default sets back to origin.
	virtual void Reset();


private:
	const float speed = 1;
	char inputL = 'a';
	char inputU = 'w';
	char inputR = 'd';
	char inputD = 's';

	Vec2<int> mousePos;
	const float sensitivity = 0.003;


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

