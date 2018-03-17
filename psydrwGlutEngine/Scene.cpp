#include "Scene.h"
#include "SceneManager.h"
#include <algorithm>
#include <functional>

Scene::Scene(std::unique_ptr<Camera> cam)
{
	mainCam = std::move(cam);
	
}


Scene::~Scene()
{
}

void Scene::Render()
{
	//Set up camera properites
	mainCam->SetCamMatrix();

	//Tell each object in the scene to handle logic updates
	for (std::unique_ptr<DisplayableObject>& o : objects)
		o->RenderObject();

	if (lights.size() > 8)
	{
		//Rearange the lights vector so that 8 closest cams are first
		std::nth_element(lights.begin(), lights.begin() + 8, lights.end(), [this](std::shared_ptr<Light> a, std::shared_ptr<Light> b) -> bool {

			const Vec3<float>& eyePos = mainCam->GetEyePos();

			//Get distance to a
			float aDist = a->GetPos().distanceTo(eyePos);
			//Get distance to be
			float bDist = b->GetPos().distanceTo(eyePos);

			return aDist < bDist;
		});
	}

	for (std::shared_ptr<Light>& l : lights)
		l->Render(GL_LIGHT0);
}

void Scene::Update(long tCurrent)
{
	//Tell camera to update.
	mainCam->Update(tCurrent);

	//Tell each object in the scene to handle logic updates
	for (std::unique_ptr<DisplayableObject>& o : objects)
		o->Update(tCurrent);

	for (std::shared_ptr<Light>& l : lights)
		l->Update(tCurrent);
}

void Scene::DrawScreenString(std::string s, Vec2<int> pos, Colour c)
{
	SceneManager::DrawScreenString(s, pos, c);
}

bool Scene::LightSortFcn(std::shared_ptr<Light> a, std::shared_ptr<Light> b)
{
	const Vec3<float>& eyePos = mainCam->GetEyePos();

	//Get distance to a
	float aDist = a->GetPos().distanceTo(eyePos);
	//Get distance to be
	float bDist = b->GetPos().distanceTo(eyePos);

	return aDist < bDist;
	
}


