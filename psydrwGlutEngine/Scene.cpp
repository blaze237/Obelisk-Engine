#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Render()
{
	//Tell each object in the scene to handle logic updates
	for (std::unique_ptr<DisplayableObject>& o : objects)
		o->Render();
}

void Scene::Update(long tCurrent)
{
		//Tell each object in the scene to handle logic updates
		for (std::unique_ptr<DisplayableObject>& o : objects)
			o->Update(tCurrent);
}
