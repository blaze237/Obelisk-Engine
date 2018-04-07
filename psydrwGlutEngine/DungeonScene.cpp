#include "DungeonScene.h"
#include "PhysicsCam.h"
#include "PhsyicsCamParent.h"
#include "Plane.h"
#include "Cube.h"

#define planeRes  50

DungeonScene::DungeonScene()
{
	//Set scene cam
	mainCam = std::make_unique<PhysicsCam>(Vec3<float>(0, 0, 0), Vec3<float>(0, 0, 1));
	std::shared_ptr<DisplayableObject> camParent = std::make_shared<PhsyicsCamParent>(Vec3<float>(0, 100, -50), Vec3<float>(5, 15, 5), "Cam", dynamic_cast<PhysicsCam&>(*mainCam));
	objects.push_back(camParent);

	PhysicsCam& d = dynamic_cast<PhysicsCam&>(*mainCam);
	dynamic_cast<PhysicsCam&>(*mainCam).RegisterParent(camParent);

	//Set up skybox
	std::vector<Texture2D> sBoxTs;
	sBoxTs.push_back(Texture2D("../textures/skybox/left.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/right.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/front.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/back.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/down.png"));
	sBoxTs.push_back(Texture2D("../textures/skybox/up.png"));

	skyBox = std::make_unique<SkyBox>(sBoxTs);
	skyBox->SetScale(mainCam->GetFarClip() / 2);


//Create scene objects

	//Ground grass outside
	std::shared_ptr<DisplayableObject> floorGrass = std::make_shared<Plane>(Vec3<float>(0, 50, -25), Texture2D("../textures/grass.jpg"), "floor", planeRes, 40, 12);
	floorGrass->SetScaleX(1000);
	floorGrass->SetScaleZ(300);
	floorGrass->SetCollidable(true);
	objects.push_back(floorGrass);
	//Ground cobble inside
	std::shared_ptr<DisplayableObject> floorGround = std::make_shared<Plane>(Vec3<float>(0, 40, 600), Texture2D("../textures/groundStone.jpg"), "floor", planeRes, 40);
	floorGround->SetScaleX(1000);
	floorGround->SetScaleZ(1000);
	floorGround->SetCollidable(true);
	objects.push_back(floorGround);

	//roof 1
	std::shared_ptr<DisplayableObject> roof = std::make_shared<Plane>(Vec3<float>(0, 125, 332.5), Texture2D("../textures/groundStone.jpg"), "roof", planeRes, 40, 16.6);
	roof->SetScaleX(1000);
	roof->SetScaleZ(415);
	roof->SetOrientationZ(180);
	objects.push_back(roof);

	//Outer Wall R
	std::shared_ptr<DisplayableObject> outerWallR = std::make_shared<Cube>(Vec3<float>(-250, 75, 130), "wall", Texture2D("../textures/cobble.jpg"), 20, 5);
	outerWallR->SetScaleX(475);
	outerWallR->SetScaleZ(10);
	outerWallR->SetScaleY(100);
	outerWallR->SetCollidable(true);
	objects.push_back(outerWallR);
	//Outer Wall REnd
	std::shared_ptr<DisplayableObject> outerWallRE = std::make_shared<Cube>(Vec3<float>(-17.4, 75, 130), "wall", Texture2D("../textures/cobble.jpg"), 0.5, 4.5);
	outerWallRE->SetScaleX(9.9);
	outerWallRE->SetScaleZ(9.9);
	outerWallRE->SetScaleY(100);
	objects.push_back(outerWallRE);

	//Outer wall keystone
	std::shared_ptr<DisplayableObject> outerWallKS = std::make_shared<Cube>(Vec3<float>(0, 110, 130), "wall", Texture2D("../textures/cobble.jpg"), 1.3, 1.3);
	outerWallKS->SetScaleX(25);
	outerWallKS->SetScaleZ(10);
	outerWallKS->SetScaleY(30);
	outerWallKS->SetCollidable(true);
	objects.push_back(outerWallKS);


	//Outer Wall L
	std::shared_ptr<DisplayableObject> outerWallL = std::make_shared<Cube>(Vec3<float>(250, 75, 130), "wall", Texture2D("../textures/cobble.jpg"), 20, 5);
	outerWallL->SetScaleX(475);
	outerWallL->SetScaleZ(10);
	outerWallL->SetScaleY(100);
	outerWallL->SetCollidable(true);
	objects.push_back(outerWallL);
	//Outer Wall LEnd
	std::shared_ptr<DisplayableObject> outerWallLE = std::make_shared<Cube>(Vec3<float>(17.4, 75, 130), "wall", Texture2D("../textures/cobble.jpg"), 0.5, 4.5);
	outerWallLE->SetScaleX(9.9);
	outerWallLE->SetScaleZ(9.9);
	outerWallLE->SetScaleY(100);
	objects.push_back(outerWallLE);

	//Step entrance
	std::shared_ptr<DisplayableObject> step = std::make_shared<Cube>(Vec3<float>(0, 40.5 , 130 ), "wall", Texture2D("../textures/groundStone.jpg"), 2, 0.8);
	step->SetScaleX(25);
	step->SetScaleZ(10);
	step->SetScaleY(20);
	step->SetCollidable(true);
	objects.push_back(step);



	//Internal walls

	//left side hallway
	std::shared_ptr<DisplayableObject> wall = std::make_shared<Cube>(Vec3<float>(30, 75, 170), "wall", Texture2D("../textures/cobble.jpg"), 3.1, 5);
	wall->SetScaleX(75);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(30, 75, 315), "wall", Texture2D("../textures/cobble.jpg"), 6.2, 5);
	wall->SetScaleX(150);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(30, 75, 460), "wall", Texture2D("../textures/cobble.jpg"), 6.2, 5);
	wall->SetScaleX(140);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	//right side hallway
	wall = std::make_shared<Cube>(Vec3<float>(-30, 75, 171), "wall", Texture2D("../textures/cobble.jpg"), 3.1, 5);
	wall->SetScaleX(90);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-30, 75, 315), "wall", Texture2D("../textures/cobble.jpg"), 6.2, 5);
	wall->SetScaleX(150);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-30, 75, 460), "wall", Texture2D("../textures/cobble.jpg"), 6.2, 5);
	wall->SetScaleX(140);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	//First left room
	wall = std::make_shared<Cube>(Vec3<float>(176, 75, 325), "wall", Texture2D("../textures/cobble.jpg"), 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(325, 75, 226), "wall", Texture2D("../textures/cobble.jpg"), 9.3, 5);
	wall->SetScaleX(200);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	//First right room
	wall = std::make_shared<Cube>(Vec3<float>(-176, 75, 325), "wall", Texture2D("../textures/cobble.jpg"), 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-325, 75, 226), "wall", Texture2D("../textures/cobble.jpg"), 9.3, 5);
	wall->SetScaleX(200);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	//Attrium Walls
	wall = std::make_shared<Cube>(Vec3<float>(-175, 75, 535), "wall", Texture2D("../textures/cobble.jpg"), 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-175, 175, 535), "wall", Texture2D("../textures/cobble.jpg"), 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(false);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(175, 75, 535), "wall", Texture2D("../textures/cobble.jpg"), 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(175, 175, 535), "wall", Texture2D("../textures/cobble.jpg"), 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(false);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(325, 75, 760), "wall", Texture2D("../textures/cobble.jpg"), 18.6, 5);
	wall->SetScaleX(450);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(325, 175, 760), "wall", Texture2D("../textures/cobble.jpg"), 18.6, 5);
	wall->SetScaleX(450);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	wall->SetCollidable(false);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-325, 75, 760), "wall", Texture2D("../textures/cobble.jpg"), 18.6, 5);
	wall->SetScaleX(450);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-325, 175, 760), "wall", Texture2D("../textures/cobble.jpg"), 18.6, 5);
	wall->SetScaleX(450);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	wall->SetCollidable(false);
	objects.push_back(wall);

}


DungeonScene::~DungeonScene()
{
}

void DungeonScene::Update(long tCurrent)
{
	Scene::Update(tCurrent);

	if (InputManager::Pressed(InputManager::ESC))
		glutDestroyWindow(1);
}
