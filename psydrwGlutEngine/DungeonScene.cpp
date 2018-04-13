#include "DungeonScene.h"
#include "PhysicsCam.h"
#include "PhsyicsCamParent.h"
#include "PlaneObj.h"
#include "Cube.h"
#include "SceneManager.h"

#define planeRes  2


DungeonScene::DungeonScene()
{
	SceneManager::SetFogParams(Colour(0, 0, 0, 1), GL_EXP, GL_NICEST, 0.007f, 0, 700);
	SceneManager::SetFog(true);

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
	skyBox->SetScale(mainCam->GetFarDist() / 2);


	//Define shared textures
	Texture2D cobbleTex("../textures/cobble.jpg");
	Texture2D grassTex("../textures/grass.jpg");
	Texture2D groundTex("../textures/groundStone.jpg");
	Texture2D mossRockTex("../textures/moss.jpg");

	//Ground and roof
	//Ground grass outside
	std::shared_ptr<DisplayableObject> floorGrass = std::make_shared<PlaneObj>(Vec3<float>(0, 50, -25), grassTex, "floor", planeRes, 40, 12);
	floorGrass->SetScaleX(1000);
	floorGrass->SetScaleZ(300);
	floorGrass->SetCollidable(true);
	objects.push_back(floorGrass);
	//Ground cobble inside
	std::shared_ptr<DisplayableObject> floorGround = std::make_shared<PlaneObj>(Vec3<float>(0, 40, 1100), groundTex, "floor", planeRes, 40, 80);
	floorGround->SetScaleX(1000);
	floorGround->SetScaleZ(2000);
	floorGround->SetCollidable(true);
	objects.push_back(floorGround);

	//roof low
	std::shared_ptr<DisplayableObject> roof = std::make_shared<PlaneObj>(Vec3<float>(0, 125, 332.5), groundTex, "roof", planeRes, 40, 16.6);
	roof->SetScaleX(1000);
	roof->SetScaleZ(415);
	roof->SetOrientationZ(180);
	objects.push_back(roof);

	//Roof high
	roof = std::make_shared<PlaneObj>(Vec3<float>(0, 225, 1032.5), groundTex, "roof", planeRes, 20.5, 40);
	roof->SetScaleX(550);
	roof->SetScaleZ(1000);
	roof->SetOrientationZ(180);
	objects.push_back(roof);

	//Outer Walls



	//Outer Wall R
	std::shared_ptr<DisplayableObject> outerWallR = std::make_shared<Cube>(Vec3<float>(-250, 75, 130), "wall", cobbleTex, 20, 5);
	outerWallR->SetScaleX(475);
	outerWallR->SetScaleZ(10);
	outerWallR->SetScaleY(100);
	outerWallR->SetCollidable(true);
	objects.push_back(outerWallR);
	//Outer Wall REnd
	std::shared_ptr<DisplayableObject> outerWallRE = std::make_shared<Cube>(Vec3<float>(-17.4, 75, 130), "wall", cobbleTex, 0.5, 4.5);
	outerWallRE->SetScaleX(9.9);
	outerWallRE->SetScaleZ(9.9);
	outerWallRE->SetScaleY(100);
	objects.push_back(outerWallRE);

	//Outer wall keystone
	std::shared_ptr<DisplayableObject> outerWallKS = std::make_shared<Cube>(Vec3<float>(0, 110, 130), "wall", cobbleTex, 1.3, 1.3);
	outerWallKS->SetScaleX(25);
	outerWallKS->SetScaleZ(10);
	outerWallKS->SetScaleY(30);
	outerWallKS->SetCollidable(true);
	objects.push_back(outerWallKS);


	//Outer Wall L
	std::shared_ptr<DisplayableObject> outerWallL = std::make_shared<Cube>(Vec3<float>(250, 75, 130), "wall", cobbleTex, 20, 5);
	outerWallL->SetScaleX(475);
	outerWallL->SetScaleZ(10);
	outerWallL->SetScaleY(100);
	outerWallL->SetCollidable(true);
	objects.push_back(outerWallL);
	//Outer Wall LEnd
	std::shared_ptr<DisplayableObject> outerWallLE = std::make_shared<Cube>(Vec3<float>(17.4, 75, 130), "wall", cobbleTex, 0.5, 4.5);
	outerWallLE->SetScaleX(9.9);
	outerWallLE->SetScaleZ(9.9);
	outerWallLE->SetScaleY(100);
	objects.push_back(outerWallLE);

	//Step entrance
	std::shared_ptr<DisplayableObject> step = std::make_shared<Cube>(Vec3<float>(0, 40.5, 130), "wall", groundTex, 2, 0.8);
	step->SetScaleX(25);
	step->SetScaleZ(10);
	step->SetScaleY(20);
	step->SetCollidable(true);
	objects.push_back(step);



	//HallWay

	//left side hallway
	std::shared_ptr<DisplayableObject> wall = std::make_shared<Cube>(Vec3<float>(60, 75, 171), "wall", cobbleTex, 3.1, 5);
	wall->SetScaleX(90);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(60, 75, 315), "wall", cobbleTex, 6.2, 5);
	wall->SetScaleX(150);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(60, 75, 460), "wall", cobbleTex, 6.2, 5);
	wall->SetScaleX(140);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	//right side hallway
	wall = std::make_shared<Cube>(Vec3<float>(-60, 75, 171), "wall", cobbleTex, 3.1, 5);
	wall->SetScaleX(90);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-60, 75, 315), "wall", cobbleTex, 6.2, 5);
	wall->SetScaleX(150);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-60, 75, 460), "wall", cobbleTex, 6.2, 5);
	wall->SetScaleX(140);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);


	//left room

	//Walls
	wall = std::make_shared<Cube>(Vec3<float>(206, 75, 325), "wall", cobbleTex, 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(325, 75, 226), "wall", cobbleTex, 9.3, 5);
	wall->SetScaleX(200);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	//right room

	//Walls
	wall = std::make_shared<Cube>(Vec3<float>(-206, 75, 325), "wall", cobbleTex, 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-325, 75, 226), "wall", cobbleTex, 9.3, 5);
	wall->SetScaleX(200);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	//Attrium 

	//Pillars



	//Walls
	wall = std::make_shared<Cube>(Vec3<float>(-145, 75, 535), "wall", cobbleTex, 10.3, 5);
	wall->SetScaleX(250);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(0, 165, 535), "wall", cobbleTex, 1.7, 6);
	wall->SetScaleX(40);
	wall->SetScaleZ(10);
	wall->SetScaleY(120);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-145, 175, 535), "wall", cobbleTex, 10.3, 5);
	wall->SetScaleX(250);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(145, 75, 535), "wall", cobbleTex, 10.3, 5);
	wall->SetScaleX(250);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(145, 175, 535), "wall", cobbleTex, 10.3, 5);
	wall->SetScaleX(250);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(275, 75, 715), "wall", cobbleTex, 14.5, 5);
	wall->SetScaleX(350);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(275, 175, 715), "wall", cobbleTex, 14.5, 5);
	wall->SetScaleX(350);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-275, 75, 715), "wall", cobbleTex, 14.5, 5);
	wall->SetScaleX(350);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-275, 175, 715), "wall", cobbleTex, 14.5, 5);
	wall->SetScaleX(350);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(0, 165, 885), "wall", cobbleTex, 1.7, 6);
	wall->SetScaleX(40);
	wall->SetScaleZ(10);
	wall->SetScaleY(120);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-145, 75, 885), "wall", cobbleTex, 10.3, 5);
	wall->SetScaleX(250);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-145, 175, 885), "wall", cobbleTex, 10.3, 5);
	wall->SetScaleX(250);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(145, 75, 885), "wall", cobbleTex, 10.3, 5);
	wall->SetScaleX(250);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(145, 175, 885), "wall", cobbleTex, 10.3, 5);
	wall->SetScaleX(250);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	objects.push_back(wall);

	//Platforming room

	//Platforms
	std::shared_ptr<DisplayableObject> platform = std::make_shared<Cube>(Vec3<float>(-170, 50, 970), "PLATFORM", mossRockTex, 3, 2);
	platform->SetScale(30);
	platform->SetScaleY(20);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(-170, 60, 1020), "wall", mossRockTex, 2, 2.7);
	platform->SetScale(30);
	platform->SetScaleY(40);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(-170, 70, 1070), "wall", mossRockTex, 2, 4.1);
	platform->SetScale(30);
	platform->SetScaleY(60);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(-170, 80, 1120), "wall", mossRockTex, 2, 5.4);
	platform->SetScale(30);
	platform->SetScaleY(80);
	platform->SetCollidable(true);
	objects.push_back(platform);



	//Walls
	wall = std::make_shared<Cube>(Vec3<float>(275, 75, 1065), "wall", cobbleTex, 14.5, 5);
	wall->SetScaleX(350);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(275, 175, 1065), "wall", cobbleTex, 14.5, 5);
	wall->SetScaleX(350);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-275, 75, 1065), "wall", cobbleTex, 14.5, 5);
	wall->SetScaleX(350);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-275, 175, 1065), "wall", cobbleTex, 14.5, 5);
	wall->SetScaleX(350);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetOrientationY(90);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-150, 75, 1230), "wall", cobbleTex, 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(-150, 175, 1230), "wall", cobbleTex, 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(150, 75, 1230), "wall", cobbleTex, 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	wall->SetCollidable(true);
	objects.push_back(wall);

	wall = std::make_shared<Cube>(Vec3<float>(150, 175, 1230), "wall", cobbleTex, 12.4, 5);
	wall->SetScaleX(300);
	wall->SetScaleZ(10);
	wall->SetScaleY(100);
	objects.push_back(wall);
}


DungeonScene::~DungeonScene()
{
}

void DungeonScene::Update(long tCurrent)
{
	Scene::Update(tCurrent);

	if (InputManager::Pressed(InputManager::ESC))
		SceneManager::Exit();
}
