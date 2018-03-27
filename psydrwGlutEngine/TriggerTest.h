#pragma once
#include "TestObject.h"
#include "Scene.h"
class TriggerTest :
	public TestObject
{
public:
	TriggerTest(Vec3<float> pos, Texture2D texture, Scene * scene);
	virtual ~TriggerTest();

	virtual void OnTrigger(std::string tag);
	virtual void Update(long tCurrent);


private:
	Scene * scene;
};

