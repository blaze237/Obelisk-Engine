#pragma once
#include "Light.h"
class TestLight :
	public Light
{
public:
	TestLight();
	virtual ~TestLight();

	virtual void Render(GLenum lightID);

	//Hanlde any movement etc
	virtual void Update(long tCurrent);
};

