
#include "SceneManager.h"
#include "TestScene.h"
#include <vector>
#include "Scene.h"
#include "MathHelp.h"
#include "Vec3.h"
#include <iostream>
int main(int argc, char **argv)
{

	Vec3<float> pos(5, 10, 0);
	Vec3<float> rot(0, 180, 0);

	Vec3<float> newPos = MathHelp::RotatePoint(pos, rot);

	std::cout << newPos.x << " " << newPos.y << " " << newPos.z << std::endl;

	//Create an instance of the engine
	SceneManager sm(argc, argv);
	//Register your scenes
	sm.AddScene(std::make_unique<TestScene>());
	//Set the scene to initialy run
	sm.SetScene(0);
	//Start the engine
	sm.Start();
	
	//Put this here so that error messages can be read before the application console auto closes
	getchar();
}

