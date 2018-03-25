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

	PhysicsUpdate();

}

void Scene::PhysicsUpdate()
{



	//Apply friction to velocity of grounded objects


	int index = 0;
	//Loop through each object in the vector
	for (std::shared_ptr<DisplayableObject>& object : objects)
	{
	
		//Non kinematic objects handle their own position and velocity logic
		if (!object->IsKinematic())
		{
			++index;
			continue;
		}

		//Apply gravity to y velocity (if y velocity is currently less than gravity)
		//
		if (object->GetVelocity().y > -gravity)
			object->SetVelocityY((object->GetVelocity().y - gravity/10.f) < -gravity ? -gravity : object->GetVelocity().y - gravity/10.f);

		//Apply friction to grounded objects
		if (object->IsGrounded())
		{
			if(object->GetVelocity().x > 0)
				object->SetVelocityX((object->GetVelocity().x - friction) < 0 ? 0 : object->GetVelocity().x - friction);
			else if(object->GetVelocity().x < 0)
				object->SetVelocityX((object->GetVelocity().x + friction) > 0 ? 0 : object->GetVelocity().x + friction);
			
			if (object->GetVelocity().z > 0)
				object->SetVelocityZ((object->GetVelocity().z - friction) < 0 ? 0 : object->GetVelocity().z - friction);
			else if (object->GetVelocity().z < 0)
				object->SetVelocityZ((object->GetVelocity().z + friction) > 0 ? 0 : object->GetVelocity().z - friction);

		}


		//Grab its current pos and velocity
		Vec3<float> posCur = object->GetPos();
		Vec3<float> velCur = object->GetVelocity();

		posCur = object->GetPos();
		velCur = object->GetVelocity();

		if(velCur.x != 0)
			PredictPosition(object, index, posCur, velCur, Vec3<float>(velCur.x, 0, 0));

		posCur = object->GetPos();
		velCur = object->GetVelocity();
		//If moving the object downwards will cause a collision, then say the object is grounded and thus will be subject to friction effects in the next physics update
		object->SetGrounded(PredictPosition(object, index, posCur, velCur, Vec3<float>(0, velCur.y, 0)));
		
		if (velCur.z != 0)
		{
			posCur = object->GetPos();
			velCur = object->GetVelocity();
			PredictPosition(object, index, posCur, velCur, Vec3<float>(0, 0, velCur.z));
		}

		++index;
	}
}

bool Scene::PredictPosition(const std::shared_ptr<DisplayableObject>&  object, int index, Vec3<float> posCur, Vec3<float> velCur, Vec3<float> velComponent)
{
	//Get predicted position after applying each velocity component
	bool collision = false;
	//Check for collisions at this position agaisnt all other objects
	for (int i = 0; i < objects.size(); ++i)
	{
		if (i == index)
			continue;

		if (CheckCollision(velComponent, object, objects[i]))
		{
			//Let the object know a collision has occured and with what
			object->OnCollide(objects[i]->TAG);
			collision = true;
			//only care about a collision not all for movement handling, but can get all for logic updates if the object being tested wishes to.
			if(!objects[i]->IsMultiCollisionMode())
				break;
		}
	}

	if (collision)
		object->SetVelocity(velCur - velComponent);
	else
		object->SetPos(posCur + velComponent);

	if (collision)
		std::cout << "col" << velComponent.y << std::endl;

	return collision;
}





bool Scene::CheckCollision(Vec3<float> posOffset, const std::shared_ptr<DisplayableObject>& obj1, const std::shared_ptr<DisplayableObject>& obj2)
{
	//Get the faces of object testing against
	std::vector<BoxFace> faces = obj2->GetBBox().GetFaces();
	//Get indicies of object being tested's bbox
	std::vector<Vec3<float>> indicies = obj1->GetBBox().GetIndicies(posOffset);

	//First iteration checks if any point of the bbox of object being tested is in the volume of the bbox of object testing against.
	//Second object does the inverse
	bool flags[3][8];
	for (int k = 0; k < 2; ++k)
	{
		//For each face pair, do yo thing
		for (int i = 0; i < 6; i += 2)
		{
			BoxFace face1 = faces[i];
			BoxFace face2 = faces[i + 1];

			bool face1Flags[8], face2Flags[8];
			int j = 0;

			//Check each indicie against face1 to see if any are behind it
			for (Vec3<float> p : indicies)
			{
				face1Flags[j] = HalfSpaceTest(face1.normal, face1.A, p);
				++j;
			}
			j = 0;
			//Check each indicie against face1 to see if any are behind it
			for (Vec3<float> p : indicies)
			{
				face2Flags[j] = HalfSpaceTest(face2.normal, face2.A, p);
				++j;
			}
			//Loop through each faceflag array, noting mathces and misses in the correspoding entry in flags array
			for (j = 0; j < 8; ++j)
				flags[i / 2][j] = face1Flags[j] && face2Flags[j];

		}

		//Loop through each flag array looking for matches between the 3
		for (int i = 0; i < 8; ++i)
		{
			if (flags[0][i] && flags[1][i] && flags[2][i])
			{
				return true;
			}
		}

		//Now need to check other way round for next loop iteration
		faces = obj1->GetBBox().GetFaces(posOffset);
		indicies = obj2->GetBBox().GetIndicies();
	}


	return false;
}

bool Scene::HalfSpaceTest(Vec3<float> normal, Vec3<float> planePoint, Vec3<float> point)
{
	//Get vector from point on plane to test point
	Vec3<float> tmp = point - planePoint;
	//Get distance to point
	float dist = tmp.DotProd(normal);

	//Point is in front of plane
	if (dist > 0)
		return false;

	//Point is behind plane
	return true;
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


