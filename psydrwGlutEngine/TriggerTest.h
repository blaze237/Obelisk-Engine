#pragma once
#include "TestObject.h"
class TriggerTest :
	public TestObject
{
public:
	TriggerTest(Vec3<float> pos, Texture2D texture);
	virtual ~TriggerTest();

	virtual void OnTrigger(std::string tag);
};

