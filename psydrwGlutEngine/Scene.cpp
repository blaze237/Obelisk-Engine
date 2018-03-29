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
	//Loop through each object in the vector
	for (std::shared_ptr<DisplayableObject>& object : objects)
	{
		//Non kinematic objects handle their own position and velocity logic
		if (!object->IsKinematic())
			continue;
		

		//Apply gravity to y velocity (if y velocity is currently less than gravity)
		if (object->GetVelocity().y > -gravity)
			object->SetVelocityY((object->GetVelocity().y - gravity / 10.f) < -gravity ? -gravity : object->GetVelocity().y - gravity / 10.f);
			//object->SetVelocityY( -gravity);

			//

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
				object->SetVelocityZ((object->GetVelocity().z + friction) > 0 ? 0 : object->GetVelocity().z + friction);
		}

	//Apply velocity in each direction if doing so wont cause a collision
		
		//Object will allways have y-velocity due to gravity, so we check this first, and use the result of collision check to determine if the object is grounded or not
		object->SetGrounded(ApplyVelocity(object,object->GetPos(), object->GetVelocity(), Vec3<float>(0, object->GetVelocity().y, 0)));
		
		//Apply x and z components of velocity.
		if(object->GetVelocity().x != 0)
			ApplyVelocity(object, object->GetPos(), object->GetVelocity(), Vec3<float>(object->GetVelocity().x, 0, 0));
		if (object->GetVelocity().z != 0)
			ApplyVelocity(object,object->GetPos(), object->GetVelocity(), Vec3<float>(0, 0, object->GetVelocity().z));

	//Apply rotational velocity in each direction if doing so wont cause a collision
		if (object->GetRotVelocity().x != 0)
			ApplyRotVelocity(object, object->GetPos(), object->GetRotVelocity(), Vec3<float>(object->GetRotVelocity().x, 0, 0));
		if (object->GetRotVelocity().y != 0)
			ApplyRotVelocity(object, object->GetPos(), object->GetRotVelocity(), Vec3<float>(0, object->GetRotVelocity().y, 0));
		if (object->GetRotVelocity().z != 0)
			ApplyRotVelocity(object, object->GetPos(), object->GetRotVelocity(), Vec3<float>(0, 0, object->GetRotVelocity().z));

	}
}

bool Scene::ApplyVelocity(const std::shared_ptr<DisplayableObject>&  object, Vec3<float> posCur, Vec3<float> velCur, Vec3<float> velComponent)
{
	//Used for recursive collision checks (if enabled)
	static int counter = 0;

	bool collision = false;
	//Check for collisions at its predicted position position agaisnt all other objects
	for (int i = 0; i < objects.size(); ++i)
	{
		//Dont want to test for collisions with self
		if(object->ID == objects[i]->ID)
			continue;

		////Check the distance to object[i], if it less than the velocity of object plus the size of its bbox's largest dimension squared then dont bother checking collisions for performance
		//float vel = MathHelp::Max3(abs(velComponent.x), abs(velComponent.y), abs(velComponent.z));
		//if (object->GetPos().distanceTo(objects[i]->GetPos()) > vel + object->GetBBox().GetLargestDimension())
		//	continue;



		if (CheckCollision(velComponent, Vec3<float>(0,0,0), object->GetBBox(), objects[i]->GetBBox()))
		{
			if (!objects[i]->GetBBox().IsTrigger() && !object->GetBBox().IsTrigger())
			{
				//Let the object know a collision has occured and with what
				if(counter == 0)
					object->OnCollide(objects[i]->TAG);
				collision = true;
				//only care about a collision not all for movement handling, but can get all for logic updates if the object being tested wishes to.
				if (!object->IsMultiCollisionMode())
					break;
			}
			//Handle possible trigger configurations
			else if (counter == 0 && objects[i]->GetBBox().IsTrigger() && !object->GetBBox().IsTrigger())
				objects[i]->OnTrigger(object->TAG);
			else if (counter == 0 && object->GetBBox().IsTrigger() && !objects[i]->GetBBox().IsTrigger())
				object->OnTrigger(objects[i]->TAG);
			else if (counter == 0 && object->GetBBox().IsTrigger() && objects[i]->GetBBox().IsTrigger())
			{
				object->OnTrigger(objects[i]->TAG);
				objects[i]->OnTrigger(object->TAG);
			}
		}
	}

	if (collision)
		object->SetVelocity(velCur - velComponent);
	else
		object->SetPos(posCur + velComponent);


	//Attempt to get objects as close to oneanother as possible if determine that an objects velocity would cause a collision. If recurssion is enabled
	if (RecurisveCollisions)
	{
		//If no collision was predicted then no need to do anything
		if (counter == 0 && !collision)
			return collision;

		//Otherwise, attempt to recursivley move the object closer to colliding objects
		if(!RecursiveCollisionsForY && counter < 1 && velComponent.y == 0)
		{
			++counter;
			ApplyVelocity(object, posCur, velCur, velComponent / 10.f);

		}
		else if (RecursiveCollisionsForY && counter < 1)
		{
			++counter;
			ApplyVelocity(object, posCur, velCur, velComponent / 10.f);
		}

		else
			counter = 0;
	}
	return collision;
}

bool Scene::ApplyRotVelocity(const std::shared_ptr<DisplayableObject>& object, Vec3<float> posCur, Vec3<float> rotCur, Vec3<float> rotComponent)
{
	//Used for recursive collision checks (if enabled)
	static int counter = 0;

	bool collision = false;
	//Check for collisions at the predicted rotation agaisnt all other objects
	for (int i = 0; i < objects.size(); ++i)
	{
		//Dont want to test for collisions with self
		if (object->ID == objects[i]->ID)
			continue;


		if (CheckCollision(Vec3<float>(0,0,0), rotComponent, object->GetBBox(), objects[i]->GetBBox()))
		{
			if (!objects[i]->GetBBox().IsTrigger() && !object->GetBBox().IsTrigger())
			{
				//Let the object know a collision has occured and with what
				object->OnCollide(objects[i]->TAG);
				collision = true;
				//only care about a collision not all for movement handling, but can get all for logic updates if the object being tested wishes to.
				if (!object->IsMultiCollisionMode())
					break;
			}
			//Handle possible trigger configurations
			else if (objects[i]->GetBBox().IsTrigger() && !object->GetBBox().IsTrigger())
				objects[i]->OnTrigger(object->TAG);
			else if (object->GetBBox().IsTrigger() && !objects[i]->GetBBox().IsTrigger())
				object->OnTrigger(objects[i]->TAG);
			else if (object->GetBBox().IsTrigger() && objects[i]->GetBBox().IsTrigger())
			{
				object->OnTrigger(objects[i]->TAG);
				objects[i]->OnTrigger(object->TAG);
			}
		}
	}

	if (collision)
		object->SetRotVelocity(rotCur - rotComponent);
	else
		object->SetOrientation(rotCur + rotComponent);


	//Attempt to get objects as close to oneanother as possible if determine that an objects velocity would cause a collision. If recurssion is enabled
	if (RecurisveCollisions)
	{
		//If no collision was predicted then no need to do anything
		if (counter == 0 && !collision)
			return collision;

		//Otherwise, attempt to recursivley move the object closer to colliding objects
		if (!RecursiveCollisionsForY && counter < 1 && rotComponent.y == 0)
		{
			++counter;
			ApplyRotVelocity(object, posCur, rotCur, rotComponent / 10.f);

		}
		else if (RecursiveCollisionsForY && counter < 1)
		{
			++counter;
			ApplyRotVelocity(object, posCur, rotCur, rotComponent / 10.f);
		}

		else
			counter = 0;
	}
	return collision;
}



bool Scene::CheckCollision(Vec3<float> posOffset, Vec3<float> rotOffset, BoundingBox obj1, BoundingBox obj2)
{
	//Get the faces of object testing against
	std::vector<BoxFace> faces = obj2.GetFaces();
	//Get indicies of object being tested's bbox
	std::vector<Vec3<float>> indicies = obj1.GetIndicies(posOffset);

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
		
			//Check each indicie against face2 to see if any are behind it
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
		faces = obj1.GetFaces(posOffset);
		indicies = obj2.GetIndicies();
	}

	return false;
}


bool Scene::CheckCollisions(DisplayableObject * obj)
{
	bool collision = false;
	for (int i = 0; i < objects.size(); ++i)
	{
		//Dont want to test for collisions with self
		if (obj->ID == objects[i]->ID)
			continue;

		//Check the distance to object[i], if it less than the velocity of object plus the size of its bbox's largest dimension squared then dont bother checking collisions for performance
		if (obj->GetPos().distanceTo(objects[i]->GetPos()) >  obj->GetBBox().GetLargestDimension())
			continue;

		if (CheckCollision(Vec3<float>(0, 0, 0), Vec3<float>(0, 0, 0), obj->GetBBox(), objects[i]->GetBBox()))
		{
			if (!objects[i]->GetBBox().IsTrigger() && !obj->GetBBox().IsTrigger())
			{
				//Let the object know a collision has occured and with what
				obj->OnCollide(objects[i]->TAG);
				collision = true;
				//only care about a collision not all for movement handling, but can get all for logic updates if the object being tested wishes to.
				if (!obj->IsMultiCollisionMode())
					break;
			}
			//Handle possible trigger configurations
			else if (objects[i]->GetBBox().IsTrigger() && !obj->GetBBox().IsTrigger())
				objects[i]->OnTrigger(obj->TAG);
			else if (obj->GetBBox().IsTrigger() && !objects[i]->GetBBox().IsTrigger())
				obj->OnTrigger(objects[i]->TAG);
			else if (obj->GetBBox().IsTrigger() && objects[i]->GetBBox().IsTrigger())
			{
				obj->OnTrigger(objects[i]->TAG);
				objects[i]->OnTrigger(obj->TAG);
			}
		}
	}

	return collision;
}

bool Scene::CheckCollisions(BoundingBox bBox, std::string tag, bool multiObjectCollissions)
{
	bool collision = false;
	for (int i = 0; i < objects.size(); ++i)
	{
		//Check the distance to object[i], if it less than the velocity of object plus the size of its bbox's largest dimension squared then dont bother checking collisions for performance
		if (bBox.GetParentPos().distanceTo(objects[i]->GetPos()) >  bBox.GetLargestDimension())
			continue;

		if (CheckCollision(Vec3<float>(0, 0, 0), Vec3<float>(0, 0, 0), bBox, objects[i]->GetBBox()))
		{
			if (!objects[i]->GetBBox().IsTrigger() && !bBox.IsTrigger())
			{
				collision = true;
				//only care about a collision not all for movement handling, but can get all for logic updates if the object being tested wishes to.
				if (multiObjectCollissions)
					break;
			}
			//Handle possible trigger configurations
			else if (objects[i]->GetBBox().IsTrigger())
				objects[i]->OnTrigger(tag);
		}
	}

	return collision;
}


bool Scene::HalfSpaceTest(Vec3<float> normal, Vec3<float> planePoint, Vec3<float> point)
{
	//Get vector from point on plane to test point
	Vec3<float> tmp = point - planePoint;
	//Get distance to point
	long double dist = tmp.DotProd(normal);

	//Point is in front of plane
	if (dist > 0)
		return false;

	//Point beind
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



