#include "TestScene.h"
#include "TestObject.h"
#include "FPSCamera.h"
#include "Spotlight.h"
#include "Colour.h"
#include <vector>
#include "Texture2D.h"
#include "SkyBox.h"
#include "TestObject2.h"
#include "TriggerTest.h"
#include "SceneManager.h"
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
	skyBox->SetScale(mainCam->GetFarClip()/2);


	//Set up the scenes objects
	std::shared_ptr<DisplayableObject> t = std::make_shared<TestObject>(Vec3<float>(0,0,-50),Texture2D("../textures/wall.jpg"));
	t->SetScale(10);
	objects.push_back(t);

	std::shared_ptr<DisplayableObject> tr = std::make_shared<TriggerTest>(Vec3<float>(15, 10, -50), Texture2D("../textures/wall.jpg"), this);
	tr->SetScale(10);
	objects.push_back(tr);

	std::shared_ptr<DisplayableObject> t3 = std::make_shared<TestObject>(Vec3<float>(-10, 10, -50), Texture2D("../textures/wall.jpg"));
	t3->SetScale(10);
	objects.push_back(t3);

	std::shared_ptr<DisplayableObject> t2 = std::make_shared<TestObject2>(Vec3<float>(0, 60, -50), nullptr);
	t2->SetScale(10);
	objects.push_back(std::move(t2));

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



