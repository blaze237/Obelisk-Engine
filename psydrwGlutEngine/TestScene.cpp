#include "TestScene.h"
#include "TestObject.h"



TestScene::TestScene()
	:Scene()
{
	//Set up the scenes objects
	//TestObject* t = new TestObject();
	std::unique_ptr<DisplayableObject> t = std::make_unique<TestObject>();


	objects.push_back(std::move(t));
}


TestScene::~TestScene()
{
}



