#include "TestScene.h"
#include "TestObject.h"
#include "FPSCamera.h"
#include "Spotlight.h"
#include "Colour.h"

TestScene::TestScene()
	:Scene(std::make_unique<FPSCamera>(Vec3<float>(0, 0, 0), Vec3<float>(0,0,-1)))
{
	//Set up the scenes objects
	
	std::unique_ptr<DisplayableObject> t = std::make_unique<TestObject>(Vec3<float>(0,0,-50));
	objects.push_back(std::move(t));

	for (int i = 0; i < 10; i++) {
		std::shared_ptr<Spotlight> l = std::make_shared<Spotlight>(Vec3<float>(1, 1, 25 + 100 * i), Colour(0.2, 0, 0), Colour(0.9, 0, 0), Colour(0.9, 0, 0), Vec3<float>(0, 0, -1));

		lights.push_back(l);
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



