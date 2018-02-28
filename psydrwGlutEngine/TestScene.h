#pragma once
#include "Scene.h"

class TestScene : public Scene	
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void Render();
	virtual void Update(long tCurrent);


private:
	int theta = 0;
	long lastTime = 0;

};

