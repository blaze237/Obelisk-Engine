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
	

};

