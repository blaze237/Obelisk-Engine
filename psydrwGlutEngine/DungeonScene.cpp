#include "DungeonScene.h"
#include "PhysicsCam.h"
#include "PhsyicsCamParent.h"
#include "PlaneObj.h"
#include "Cube.h"
#include "SceneManager.h"
#include "CullPlane.h"
#include "CullPlaneSwitch.h"
#include "Chest.h"
#include "ShadowPlane.h"
#include "AllignedSprite.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Torch.h"
#include "Spotlight.h"
#include "PointLight.h"
#include "Throwable.h"

#define planeRes  20


DungeonScene::DungeonScene()
{
	SceneManager::SetFogParams(Colour(0, 0, 0, 1), GL_EXP2, GL_NICEST, 0.003f, 0, 700);
	SceneManager::SetFog(true);


	std::shared_ptr<DisplayableObject> throwable = std::make_shared<Throwable>(Vec3<float>(0,0,0), Texture2D("../textures/wood.png"));
	throwable->SetScale(4);
	objects.push_back(throwable);

	//Set scene cam
	mainCam = std::make_unique<PhysicsCam>(Vec3<float>(0, 0, 0), Vec3<float>(0, 0, 1), dynamic_cast<Throwable&>(*throwable));
	std::shared_ptr<DisplayableObject> camParent = std::make_shared<PhsyicsCamParent>(Vec3<float>(0, 100, -78), Vec3<float>(5, 15, 5), "Cam", dynamic_cast<PhysicsCam&>(*mainCam));
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
	Texture2D cobbleTex("../textures/stone.jpg");
	Texture2D grassTex("../textures/grass.jpg");
	Texture2D groundTex("../textures/groundStone.jpg");
	Texture2D mossRockTex("../textures/mossDark.jpg");
	Texture2D bushTex("../textures/bush.png");
	Texture2D flameSprites("../textures/flameSprites.png");


	//Cull plane 1
	std::shared_ptr<DisplayableObject> cullPlane = std::make_shared<CullPlane>(Vec3<float>(0, 50, 100), dynamic_cast<PhysicsCam&>(*mainCam));
	cullPlane->SetScaleX(600);
	cullPlane->SetScaleZ(200);
	cullPlane->SetOrientationX(-90);
	objects.push_back(cullPlane);

	cullPlane = std::make_shared<CullPlane>(Vec3<float>(0, 50, 100), dynamic_cast<PhysicsCam&>(*mainCam), -1);
	cullPlane->SetScaleX(600);
	cullPlane->SetScaleZ(200);
	cullPlane->SetOrientationX(90);
	cullPlane->SetRenderable(false);
	objects.push_back(cullPlane);


	//Only turn on the second cull plane when pass through this trigger
	std::shared_ptr<DisplayableObject> revCullplaneTrigger = std::make_shared<CullPlaneSwitch>(Vec3<float>(0, 60.5, 538), "trigger", dynamic_cast<CullPlane&>(*cullPlane));
	revCullplaneTrigger->SetScaleX(50);
	revCullplaneTrigger->SetScaleZ(1);
	revCullplaneTrigger->SetScaleY(50);
	revCullplaneTrigger->SetCollidable(true);
	revCullplaneTrigger->SetRenderable(false);
	revCullplaneTrigger->SetIsTrigger(true);
	objects.push_back(revCullplaneTrigger);

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
	std::shared_ptr<DisplayableObject> roof = std::make_shared<PlaneObj>(Vec3<float>(0, 125, 332.5), groundTex, "roof", planeRes, 26, 16.6);
	roof->SetScaleX(650);
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
	std::shared_ptr<DisplayableObject> outerWallR = std::make_shared<Cube>(Vec3<float>(-170, 75, 130), "wall", cobbleTex, 13.3, 5);
	outerWallR->SetScaleX(315);
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
	std::shared_ptr<DisplayableObject> outerWallL = std::make_shared<Cube>(Vec3<float>(170, 75, 130), "wall", cobbleTex, 13.3, 5);
	outerWallL->SetScaleX(315);
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



//Bushes 
	std::shared_ptr<DisplayableObject> bush = std::make_shared<Cube>(Vec3<float>(0, 60, -90), "bush", bushTex,40, 2);
	bush->SetScaleX(400);
	bush->SetScaleZ(10);
	bush->SetScaleY(20);
	bush->SetCollidable(true);
	objects.push_back(bush);

	bush = std::make_shared<Cube>(Vec3<float>(200, 60, 14), "bush", bushTex, 22, 2);
	bush->SetScaleX(220);
	bush->SetScaleZ(10);
	bush->SetScaleY(20);
	bush->SetOrientationY(90);
	bush->SetCollidable(true);
	objects.push_back(bush);

	bush = std::make_shared<Cube>(Vec3<float>(-200, 60, 14), "bush", bushTex, 22, 2);
	bush->SetScaleX(220);
	bush->SetScaleZ(10);
	bush->SetScaleY(20);
	bush->SetOrientationY(90);
	bush->SetCollidable(true);
	objects.push_back(bush);


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


//Targets
	std::shared_ptr<DisplayableObject> target = std::make_shared<PlaneObj>(Vec3<float>(319, 75, 225), Texture2D("../textures/target.png"), "TARGET", planeRes, 1);
	target->SetScaleX(30);
	target->SetScaleZ(30);
	target->SetScaleY(8);
	target->SetOrientationZ(90);
	target->SetCollidable(true);
	target->SetColliderRenderer(true);
	objects.push_back(target);

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
	std::shared_ptr<DisplayableObject> pillar = std::make_shared<Cylinder>(Vec3<float>(-195, 40, 605), "pillar", mossRockTex , 4, 15);
	pillar->SetScale(25);
	pillar->SetScaleY(200);
	pillar->SetCollidable(true);
	objects.push_back(pillar);

	pillar = std::make_shared<Cylinder>(Vec3<float>(-195, 40, 705), "pillar", mossRockTex, 4, 15);
	pillar->SetScale(25);
	pillar->SetScaleY(200);
	pillar->SetCollidable(true);
	objects.push_back(pillar);

	pillar = std::make_shared<Cylinder>(Vec3<float>(-195, 40, 805), "pillar", mossRockTex, 4, 15);
	pillar->SetScale(25);
	pillar->SetScaleY(200);
	pillar->SetCollidable(true);
	objects.push_back(pillar);


	pillar = std::make_shared<Cylinder>(Vec3<float>(195, 40, 605), "pillar", mossRockTex, 4, 15);
	pillar->SetScale(25);
	pillar->SetScaleY(200);
	pillar->SetCollidable(true);
	objects.push_back(pillar);

	pillar = std::make_shared<Cylinder>(Vec3<float>(195, 40, 705), "pillar", mossRockTex, 4, 15);
	pillar->SetScale(25);
	pillar->SetScaleY(200);
	pillar->SetCollidable(true);
	objects.push_back(pillar);

	pillar = std::make_shared<Cylinder>(Vec3<float>(195, 40, 805), "pillar", mossRockTex, 4, 15);
	pillar->SetScale(25);
	pillar->SetScaleY(200);
	pillar->SetCollidable(true);
	objects.push_back(pillar);

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
	objects.push_back(std::move(platform));

	platform = std::make_shared<Cube>(Vec3<float>(-170, 60, 1020), "PLATFORM", mossRockTex, 2, 2.7);
	platform->SetScale(30);
	platform->SetScaleY(40);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(-170, 70, 1070), "PLATFORM", mossRockTex, 2, 4.1);
	platform->SetScale(30);
	platform->SetScaleY(60);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(-170, 80, 1120), "PLATFORM", mossRockTex, 2, 5.4);
	platform->SetScale(30);
	platform->SetScaleY(80);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(-90, 80, 1120), "PLATFORM", mossRockTex, 2, 5.4);
	platform->SetScale(30);
	platform->SetScaleY(80);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(-10, 80, 1120), "PLATFORM", mossRockTex, 2, 5.4);
	platform->SetScale(30);
	platform->SetScaleY(80);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(70, 70, 1120), "PLATFORM", mossRockTex, 2, 4.1);
	platform->SetScale(30);
	platform->SetScaleY(60);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(140, 70, 1120), "PLATFORM", mossRockTex, 2, 5.4);
	platform->SetScale(30);
	platform->SetScaleY(80);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(210, 80, 1120), "PLATFORM", mossRockTex, 2, 5.4);
	platform->SetScale(30);
	platform->SetScaleY(80);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(210, 80, 1045), "PLATFORM", mossRockTex, 2, 5.4);
	platform->SetScale(30);
	platform->SetScaleY(80);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(150, 70, 1000), "PLATFORM", mossRockTex, 2, 4.1);
	platform->SetScale(30);
	platform->SetScaleY(60);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(90, 70, 1040), "PLATFORM", mossRockTex, 2, 4.1);
	platform->SetScale(30);
	platform->SetScaleY(60);
	platform->SetCollidable(true);
	objects.push_back(platform);

	platform = std::make_shared<Cube>(Vec3<float>(20, 60, 1000), "PLATFORM", mossRockTex, 4, 2.7);
	platform->SetScaleX(60);
	platform->SetScaleZ(30);
	platform->SetScaleY(40);
	platform->SetCollidable(true);
	objects.push_back(platform);

//Treasure chest
	std::shared_ptr<DisplayableObject> chest = std::make_shared<Chest>(Vec3<float>(7, 85, 1000), "treasure", Texture2D("../textures/chest2.png"), 1, 1);
	chest->SetScaleX(20);
	chest->SetScaleZ(10);
	chest->SetScaleY(10);
	chest->SetOrientationY(-90);
	chest->SetCollidable(true);
	chest->SetIsTrigger(true);
	objects.push_back(chest);

	std::shared_ptr<DisplayableObject> chestCollider = std::make_shared<Cube>(Vec3<float>(7, 85, 1000), "treasure_col", Texture2D("../textures/chest2.png"));
	chestCollider->SetScaleX(20);
	chestCollider->SetScaleZ(10);
	chestCollider->SetScaleY(10);
	chestCollider->SetOrientationY(-90);
	chestCollider->SetCollidable(true);
	chestCollider->SetRenderable(false);
	objects.push_back(chestCollider);

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


//Torches. Drawn near end for proper alpha blending

	//Right main hall
	std::shared_ptr<DisplayableObject> torch = std::make_shared<Torch>(Vec3<float>(-53, 64, 300), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, -30), 2);
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	std::shared_ptr<PointLight> light = std::make_shared<PointLight>(Vec3<float>(-53, 70, 300), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(-53, 64, 470), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, -30), 2);
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(-53, 70, 470), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));


	//Left main hall
	torch = std::make_shared<Torch>(Vec3<float>(53, 64, 300), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 30), 2, Vec3<float>(0.1, 1.15, 0));
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(53, 70, 300), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(53, 64, 470), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 30), 2, Vec3<float>(0.1, 1.15, 0));
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(53, 70, 470), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));


	//Right Room
	torch = std::make_shared<Torch>(Vec3<float>(-67, 64, 270), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 30), 2, Vec3<float>(0.1, 1.15, 0));
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(-85, 70, 270), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(-67, 64, 180), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 30), 2, Vec3<float>(0.1, 1.15, 0));
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(-85, 70, 180), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));


	//Left room
	torch = std::make_shared<Torch>(Vec3<float>(67, 64, 270), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, -30), 2);
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(85, 70, 270), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(67, 64, 180), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, -30), 2);
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(85, 70, 180), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));



//Atrium
	//Left pillars
	torch = std::make_shared<Torch>(Vec3<float>(-181, 74, 605), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, -30), 2);
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(-170, 80, 605), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(-181, 74, 705), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, -30), 2);
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(-170, 80, 705), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(-181, 74, 805), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, -30), 2);
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(-170, 80, 805), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	//Right pillars
	torch = std::make_shared<Torch>(Vec3<float>(181, 74, 605), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 30), 2, Vec3<float>(0.1, 1.15, 0));
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(170, 80, 605), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(181, 74, 705), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 30), 2, Vec3<float>(0.1, 1.15, 0));
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(170, 80, 705), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(181, 74, 805), Texture2D("../textures/wood.png"), flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 30), 2, Vec3<float>(0.1, 1.15, 0));
	torch->SetScaleX(6);
	torch->SetScaleZ(6);
	torch->SetScaleY(12);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(170, 80, 805), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

//Platforming room
	torch = std::make_shared<Torch>(Vec3<float>(0, 127, 1220), mossRockTex, flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(-30, 0, 0), 2, Vec3<float>(0, 1.15, 0.1));
	torch->SetScaleX(20);
	torch->SetScaleZ(20);
	torch->SetScaleY(40);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(0, 172, 1200), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	light->SetRadius(12);
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(0, 127, 895), mossRockTex, flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(30, 0, 0), 2, Vec3<float>(0, 1.15, -0.1));
	torch->SetScaleX(20);
	torch->SetScaleZ(20);
	torch->SetScaleY(40);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(0, 172, 900), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	light->SetRadius(12);
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(265, 127, 1050), mossRockTex, flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 30), 2, Vec3<float>(0.1, 1.15,0 ));
	torch->SetScaleX(20);
	torch->SetScaleZ(20);
	torch->SetScaleY(40);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(250, 172, 1050), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	light->SetRadius(12);
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(-265, 127, 1050), mossRockTex, flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, -30), 2, Vec3<float>(-0.1, 1.15, 0));
	torch->SetScaleX(20);
	torch->SetScaleZ(20);
	torch->SetScaleY(40);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(-250, 172, 1050), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	light->SetRadius(12);
	lights.push_back(std::move(light));

//Outdoor fire challices
	torch = std::make_shared<Torch>(Vec3<float>(-60, 52, 10), mossRockTex, flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 0), 2, Vec3<float>(0, 1.15, 0));
	torch->SetScaleX(20);
	torch->SetScaleZ(20);
	torch->SetScaleY(40);
	torch->SetCollidable(true);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(-60, 70, 10), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));

	torch = std::make_shared<Torch>(Vec3<float>(60, 52, 10), mossRockTex, flameSprites, "torch", dynamic_cast<Camera&>(*mainCam), 25, 256, 40, Vec3<float>(0, 0, 0), 2, Vec3<float>(0, 1.15, 0));
	torch->SetScaleX(20);
	torch->SetScaleZ(20);
	torch->SetScaleY(40);
	torch->SetCollidable(true);
	objects.push_back(torch);
	light = std::make_shared<PointLight>(Vec3<float>(60, 70, 10), Colour(0.901f, 0.678f, 0.078f, 1.0f), Vec3<int>(90, 68, 8), Colour(1.0f, 1.0f, 1.0f, 1.0f));
	lights.push_back(std::move(light));


//Player shadow. Must be last thing rendered for proper alpha blending
	std::shared_ptr<DisplayableObject> shad = std::make_shared<ShadowPlane>(Vec3<float>(0, 52, -50), Texture2D("../textures/shadow.png"), "floor", dynamic_cast<DisplayableObject&>(*camParent), 10);
	shad->SetScaleX(10);
	shad->SetScaleZ(10);
	objects.push_back(shad);

}


DungeonScene::~DungeonScene()
{
}

void DungeonScene::Update(long tCurrent)
{
	Scene::Update(tCurrent);

	if (mainCam->GetEyePos().y  < 0)
	{
		mainCam->SetEyePos(Vec3<float>(0, 100, -50));
		mainCam->SetViewDir(Vec3<float>(0, 0, 1));
	}

	if (InputManager::Pressed(InputManager::ESC))
		SceneManager::Exit();
}
