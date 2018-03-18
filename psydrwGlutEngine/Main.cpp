#include "SceneManager.h"
#include "TestScene.h"
#include <vector>
#include "Scene.h"


int main(int argc, char **argv)
{
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

