#pragma once
#include <GL/glut.h>
#include "Vec3.h"
#include "Colour.h"
class Light
{
public:
	Light(Vec3<float> position, Colour amb, Vec3<int> dif, Colour spec, bool directional);
	virtual ~Light();

	//Use this function for actualy registering the light with opengl.
	//This should only be called externaly by the scene, which will specify the 8 closest lights to draw and give them an ID to use
	virtual void Render(GLenum lightID) = 0;

	//Hanlde any movement etc
	virtual void Update(long tCurrent) = 0;

	inline bool IsPositional() const
	{
		return pos[3] == 1.0f ? true : false;
	}

	//Setter functions, wrap arrays with Vec3's and Colour's to make it nicer to use
	inline void SetPos(Vec3<float> position)
	{
		pos[0] = position.x;
		pos[1] = position.y;
		pos[2] = position.z;
	}

	inline Vec3<float> GetPos()
	{
		return Vec3<float>(pos[0], pos[1], pos[2]);
	}

	inline void SetAmbient(Colour ambient)
	{
		amb[0] = ambient.r;
		amb[1] = ambient.g;
		amb[2] = ambient.b;
		amb[3] = ambient.a;
	}

	inline void SetDiffuse(Colour diffuse)
	{
		dif[0] = diffuse.r;
		dif[1] = diffuse.g;
		dif[2] = diffuse.b;
		dif[3] = diffuse.a;
	}

	inline void SetSpecular(Colour specular)
	{
		spec[0] = specular.r;
		spec[1] = specular.g;
		spec[2] = specular.b;
		spec[3] = specular.a;
	}

	inline virtual void SetRadius(float r)
	{
		radius = r;
	}

	inline float GetRadius() const
	{
		return radius;
	}





protected:
	float pos[4];
	GLfloat amb[4];
	GLfloat dif[4];
	GLfloat spec[4];
	//Radius of the lights influence. Used to set attenuation
	float radius = 5;

	void DebugRender();
};

