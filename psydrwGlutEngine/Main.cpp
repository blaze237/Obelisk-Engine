#include "SceneManager.h"
#include "TestScene.h"
#include <vector>
#include "Scene.h"


int main(int argc, char **argv)
{
	SceneManager sm;
	sm.AddScene(std::make_unique<TestScene>());
	sm.Init(argc, argv);
}

