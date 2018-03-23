#pragma once
#include <GL/glut.h>
#include "Vec3.h"
#include "BoundingBox.h"
class DisplayableObject
{
public:
	DisplayableObject(Vec3<float> pos, Vec3<float> bBoxSize, Vec3<float> scale = Vec3<float>(1,1,1), Vec3<float> orientation = Vec3<float>(0,0,0));
	virtual ~DisplayableObject();

	//Calls your render function and handles matrix translations needed to draw at the correct position, scale and orientation. 
	//Not intended to be overiden
	void RenderObject();

	//Overide this with your own render code. Dont call directly, is called by RenderObject
	virtual void Render() = 0;
	//Default empty update. Overide for logic/animations/phsyics etc
	virtual void Update(long tCurrent);


	//Getters
	inline Vec3<float> GetPos() const
	{
		return pos;
	}
	inline Vec3<float> GetScale() const
	{
		return scale;
	}
	inline Vec3<float> GetOrientation() const
	{
		return orientation;
	}

	inline const BoundingBox& GetBBox() const
	{
		return bBox;
	}

	//Setters
	inline void SetPos(const Vec3<float>& p)
	{
		pos = p;
	}
	inline void SetScale(float s)
	{
		scale.x = scale.y = scale.z = s;
	}
	inline void SetScale(const Vec3<float>& s)
	{
		scale = s;
	}
	inline void SetOrientation(const Vec3<float>& o)
	{
		orientation = o;
	}


protected:
	Vec3<float> pos;
	Vec3<float> scale;
	Vec3<float> orientation;
	BoundingBox bBox;


};

