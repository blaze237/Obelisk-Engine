#include "TestScene.h"
#include "TestObject.h"



TestScene::TestScene()
	:Scene()
{
	//Set up the scenes objects
	//TestObject* t = new TestObject();
	for (int i = 0; i < 1; ++i) {
		std::unique_ptr<DisplayableObject> t = std::make_unique<TestObject>();
		objects.push_back(std::move(t));
	}
}


TestScene::~TestScene()
{
}



