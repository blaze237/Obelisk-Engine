#include "TriggerTest.h"
#include <iostream>


TriggerTest::TriggerTest(Vec3<float> pos, Texture2D texture, Scene * scene)
	:TestObject(pos, texture, "trig"), scene(scene)
{
	bBox.SetTrigger(true);
}


TriggerTest::~TriggerTest()
{
}

void TriggerTest::OnTrigger(std::string tag)
{
	std::cout << tag << std::endl;
}

void TriggerTest::Update(long tCurrent)
{
	scene->CheckCollisions(this);
}
