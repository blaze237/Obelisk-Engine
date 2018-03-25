#include "TriggerTest.h"
#include <iostream>


TriggerTest::TriggerTest(Vec3<float> pos, Texture2D texture)
	:TestObject(pos, texture)
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
