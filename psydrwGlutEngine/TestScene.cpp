#include "TestScene.h"
#include "TestObject.h"
#include "FPSCamera.h"


TestScene::TestScene()
	:Scene(std::make_unique<FPSCamera>(Vec3<float>(0, 0, 0), Vec3<float>(0.08208, -0.02795, -0.9962)))
{
	//Set up the scenes objects
	//TestObject* t = new TestObject();
	for (int i = 0; i < 1; ++i) {
		std::unique_ptr<GameObject> t = std::make_unique<TestObject>();
		objects.push_back(std::move(t));
	}

}


TestScene::~TestScene()
{
}

void TestScene::Render()
{
	Scene::Render();
	Scene::DrawScreenString("TEST", Vec2<int>(100, 100));
}

void TestScene::Update(long tCurrent)
{
	Scene::Update(tCurrent);

	if (InputManager::Pressed(InputManager::ESC))
		glutDestroyWindow(1);
}



