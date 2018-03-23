#pragma once
#include "TestObject.h"
#include <memory>
class TestObject2 :
	public TestObject
{
public:
	TestObject2(Vec3<float> pos, std::shared_ptr<DisplayableObject> testOb,  Texture2D texture = Texture2D(""));
	~TestObject2();

	virtual void Update(long tCurrent);

	void CheckCollision();

private:
	int theta = 0;

	long lastTime = 0;
	std::shared_ptr<DisplayableObject> testOb;
};

