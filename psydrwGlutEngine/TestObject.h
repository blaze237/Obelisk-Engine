#pragma once
#include "DisplayableObject.h"


#define timeStep  10
class TestObject :
	public GameObject
{
public:
	TestObject();
	~TestObject();

	virtual void Render();
	virtual void Update(long tCurrent);
	void drawCube(float radius);

private:
	int theta = 0;
	long lastTime = 0;
};

