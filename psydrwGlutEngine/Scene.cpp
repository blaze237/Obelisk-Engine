#include "Scene.h"
#include "SceneManager.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Render()
{
	//Set up camera properites
	mainCam.SetCamMatrix();

	//Tell each object in the scene to handle logic updates
	for (std::unique_ptr<GameObject>& o : objects)
		o->Render();
}

void Scene::Update(long tCurrent)
{
	//Tell camera to update.
	mainCam.Update(tCurrent);

	//Tell each object in the scene to handle logic updates
	for (std::unique_ptr<GameObject>& o : objects)
		o->Update(tCurrent);
}

void Scene::DrawScreenString(std::string s, Vec2<int> pos, Colour c)
{
	SceneManager::DrawScreenString(s, pos, c);
}


