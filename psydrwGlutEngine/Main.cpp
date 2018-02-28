#include "SceneManager.h"
#include "TestScene.h"
#include <vector>
#include "Scene.h"

int main(int argc, char **argv)
{
	TestScene* t = new TestScene();

	std::vector<Scene*> scenes;
	scenes.push_back(t);

	SceneManager sm(scenes);

	sm.Init(argc, argv);

	delete t;


}

