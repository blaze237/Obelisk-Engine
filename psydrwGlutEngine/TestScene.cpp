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
#include "Plane.h"
#include "PhsyicsCamParent.h"
#include "PhysicsCam.h"
TestScene::TestScene()
{
	//Set scene cam
	mainCam = std::make_unique<PhysicsCam>(Vec3<float>(0, 0, 0), Vec3<float>(0, 0, -1));
	std::shared_ptr<DisplayableObject> camParent = std::make_shared<PhsyicsCamParent>(Vec3<float>(0, 100, -50), Vec3<float>(5, 15, 5), "Cam", dynamic_cast<PhysicsCam&>(*mainCam));
	objects.push_back(camParent);

	PhysicsCam& d = dynamic_cast<PhysicsCam&>(*mainCam);
	dynamic_cast<PhysicsCam&>(*mainCam).RegisterParent(camParent);
	//Make and set scene skybox

	//Skybox textures
	std::vector<Texture2D> sBoxTs;
	sBoxTs.push_back(Texture2D("../textures/skybox/left.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/right.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/front.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/back.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/down.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/up.png"));

	//sBoxTs.push_back(Texture2D("../textures/skybox/skybox_left.png"));
	//sBoxTs.push_back(Texture2D("../textures/skybox/skybox_right.png"));
	//sBoxTs.push_back(Texture2D("../textures/skybox/skybox_front.png"));
	//sBoxTs.push_back(Texture2D("../textures/skybox/skybox_back.png"));
	//sBoxTs.push_back(Texture2D("../textures/skybox/skybox_down.png"));
	//sBoxTs.push_back(Texture2D("../textures/skybox/skybox_up.png"));

	skyBox = std::make_unique<SkyBox>(sBoxTs);
	skyBox->SetScale(mainCam->GetFarClip()/2);


	////Set up the scenes objects
	std::shared_ptr<DisplayableObject> t = std::make_shared<TestObject>(Vec3<float>(0,0,-50),Texture2D("../textures/stone.jpg"));
	t->SetScale(10);
	objects.push_back(t);

	std::shared_ptr<DisplayableObject> t3 = std::make_shared<TestObject>(Vec3<float>(0, 0, -100), Texture2D("../textures/stone.jpg"));
	t3->SetScale(10);
	t3->SetScaleX(500);
	t3->SetScaleY(200);

	objects.push_back(t3);

	std::shared_ptr<DisplayableObject> floor = std::make_shared<Plane>(Vec3<float>(0, 0, -25), Texture2D("../textures/grass.jpg"), "floor", 50, 40);
	floor->SetScaleX(1000);
	floor->SetScaleZ(1000);
	floor->SetCollidable(true);
	objects.push_back(floor);



	for (int i = 0; i < 20; i++)
	{
		std::shared_ptr<DisplayableObject> t3 = std::make_shared<TestObject>(Vec3<float>(-10*i, 10*i, -50), Texture2D("../textures/stone.jpg"));
		t3->SetScale(10);
		objects.push_back(t3);

	}

	//std::shared_ptr<DisplayableObject> t2 = std::make_shared<TestObject2>(Vec3<float>(0, 60, -50), nullptr);
	//t2->SetScale(1);
	////t2->SetScaleY(30);
	//objects.push_back(std::move(t2));


//	 std::shared_ptr<Spotlight> l = std::make_shared<Spotlight>(Vec3<float>(0, 10, 25), Colour(0.2, 0, 0), Colour(0.9, 0, 0), Colour(0.9, 0, 0), Vec3<float>(0, 0, -2));

	//Move to avoid pointless incrmenent and decrement of shared pointer counters as the inital ones imediatley go out of scope anyway
	//lights.push_back(std::move(l));
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



