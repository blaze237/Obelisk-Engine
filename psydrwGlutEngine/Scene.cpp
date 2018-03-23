#include "Scene.h"
#include "SceneManager.h"
#include <algorithm>
#include <functional>

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Render()
{
	//Set up camera properites
	mainCam->SetCamMatrix();

	RenderSky();

	//Tell each object in the scene to render itself
	for (std::shared_ptr<DisplayableObject>& o : objects)
		o->RenderObject();

	//Render the lights
	if (lights.size() > 8)
	{
		//Rearange the lights vector so that 8 closest cams are first
		std::nth_element(lights.begin(), lights.begin() + 8, lights.end(), [this](std::shared_ptr<Light>& a, std::shared_ptr<Light>& b) -> bool {

			const Vec3<float>& eyePos = mainCam->GetEyePos();

			//Get distance to a
			float aDist = a->GetPos().distanceTo(eyePos);
			//Get distance to be
			float bDist = b->GetPos().distanceTo(eyePos);

			return aDist < bDist;
		});

		for (int i = 0; i < 8; ++i)
			lights[i]->Render(LIGHT_IDS[i]);
	}
	else
	{
		int i = 0;
		for (std::shared_ptr<Light>& l : lights)
			l->Render(LIGHT_IDS[i++]);
	}
}

void Scene::Update(long tCurrent)
{
	//Tell camera to update.
	mainCam->Update(tCurrent);

	//Tell each light to to handle logic updates
	for (std::shared_ptr<Light>& l : lights)
		l->Update(tCurrent);

	//Tell each object in the scene to handle logic updates
	for (std::shared_ptr<DisplayableObject>& o : objects)
		o->Update(tCurrent);

}

void Scene::RenderSky()
{
	Vec3<float> eyePos = mainCam->GetEyePos();
	glPushMatrix();
	glTranslatef(eyePos.x, eyePos.y - skyBox->GetScale().y / 2, eyePos.z);
	skyBox->Render();
	glPopMatrix();
}

void Scene::DrawScreenString(std::string s, Vec2<int> pos, Colour c)
{
	SceneManager::DrawScreenString(s, pos, c);
}

bool Scene::LightSortFcn(std::shared_ptr<Light>& a, std::shared_ptr<Light>& b)
{
	const Vec3<float>& eyePos = mainCam->GetEyePos();

	//Get distance to a
	float aDist = a->GetPos().distanceTo(eyePos);
	//Get distance to be
	float bDist = b->GetPos().distanceTo(eyePos);

	return aDist < bDist;
	
}


