#include "TestScene.h"
#include "TestObject.h"
#include "FPSCamera.h"
#include "Spotlight.h"
#include "Colour.h"
#include <vector>
#include "Texture2D.h"
#include "SkyBox.h"
TestScene::TestScene()
{
	//Set scene cam
	mainCam = std::make_unique<FPSCamera>(Vec3<float>(0, 0, 0), Vec3<float>(0, 0, -1));

	//Make and set scene skybox

	//Skybox textures
	std::vector<Texture2D> sBoxTs;
	sBoxTs.push_back(Texture2D("../textures/skybox/skybox_left.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/skybox_right.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/skybox_front.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/skybox_back.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/skybox_down.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/skybox_up.png"));

	skyBox = std::make_unique<SkyBox>(sBoxTs);

	//Set up the scenes objects
	std::unique_ptr<DisplayableObject> t = std::make_unique<TestObject>(Vec3<float>(0,0,-50),Texture2D("../textures/wall.jpg"));
	t->SetScale(10);
	objects.push_back(std::move(t));

	//Make the lights for scene
	for (int i = 0; i < 10; i++) {
		std::shared_ptr<Spotlight> l = std::make_shared<Spotlight>(Vec3<float>(1, 1, 25 + 100 * i), Colour(0.2, 0, 0), Colour(0.9, 0, 0), Colour(0.9, 0, 0), Vec3<float>(0, 0, -1));

		//Move to avoid pointless incrmenent and decrement of shared pointer counters as the inital ones imediatley go out of scope anyway
		lights.push_back(std::move(l));
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



