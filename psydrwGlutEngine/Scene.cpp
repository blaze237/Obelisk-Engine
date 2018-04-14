#include "Scene.h"
#include "SceneManager.h"
#include <algorithm>
#include <functional>
#include "Plane.h"

#define ALLIGNED_COLLISIONS
Scene::Scene()
{
}


Scene::~Scene()
{
}

bool Scene::ObjectInFrustumBBox(std::shared_ptr<DisplayableObject>& object, std::vector<Plane>& frustum)
{
	float dist = 0;
	bool inFrustum = false;
	std::vector<Vec3<float>> inds = object->GetBBox().GetIndicies();

	Plane p = frustum[1];

	for (Plane p : frustum)
	{
		bool inFrontPlane = false;
		for (Vec3<float> i : inds)
		{
			dist = p.DistTo(i);
			if ( dist > 0)
			{
				inFrontPlane = true;
				break;
			}
		}

		//If no corneres were on the right side of the plane, then the box cannot be in the frustum
		if (!inFrontPlane)
			return false;
		//Otherwise, store the result
		inFrustum = inFrontPlane;
	}

	return inFrustum;
}

//We dont distinguish between frustum in and intersection. Just treat as being in the frustrum.
bool Scene::ObjectInFrustum(std::shared_ptr<DisplayableObject>& object, std::vector<Plane>& frustum)
{
	float dist;
	float radius = object->GetBBox().GetLargestDimension();
	Vec3<float> pos = object->GetPos();


	int k = 0;
	for (Plane p : frustum)
	{
		dist = p.DistTo(pos);

		if (dist < -radius)
			return false;

	}

	return true;

}

void Scene::Render()
{
	//Set up camera properites
	mainCam->SetCamMatrix();

	RenderSky();
	//Grab camera frustum
	std::vector<Plane> frustum = mainCam->GetFrustum();
	//Tell each object in the scene to render itself
	for (std::shared_ptr<DisplayableObject>& o : objects)
	{
		//Only render object if it is within the camera frustum
		if (!ObjectInFrustumBBox(o, frustum))
		{
			continue;
		}
		o->RenderObject();
	}


	//TODO
		//Set flag for each light to say if it is within the frustum or not. Then get 8 closest in frustum

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

	

	//Apply velocity in each direction if doing so wont cause a collision
		

		//Object will allways have y-velocity due to gravity, so we check this first, and use the result of collision check to determine if the object is grounded or not
		if(object->IsGrounded())
			object->SetGrounded(ApplyVelocity(object,object->GetPos(), object->GetVelocity(), Vec3<float>(0, object->GetVelocity().y, 0), object->GetGroundID()));
		else
			object->SetGrounded(ApplyVelocity(object, object->GetPos(), object->GetVelocity(), Vec3<float>(0, object->GetVelocity().y, 0)));

		//Apply friction to grounded objects
		if (object->IsGrounded())
		{
			if (object->GetVelocity().x > 0)
				object->SetVelocityX((object->GetVelocity().x - friction) < 0 ? 0 : object->GetVelocity().x - friction);
			else if (object->GetVelocity().x < 0)
				object->SetVelocityX((object->GetVelocity().x + friction) > 0 ? 0 : object->GetVelocity().x + friction);

			if (object->GetVelocity().z > 0)
				object->SetVelocityZ((object->GetVelocity().z - friction) < 0 ? 0 : object->GetVelocity().z - friction);
			else if (object->GetVelocity().z < 0)
				object->SetVelocityZ((object->GetVelocity().z + friction) > 0 ? 0 : object->GetVelocity().z + friction);
		}



		//Apply x and z components of velocity.
		if(object->GetVelocity().x != 0)
			ApplyVelocity(object, object->GetPos(), object->GetVelocity(), Vec3<float>(object->GetVelocity().x, 0, 0));
		if (object->GetVelocity().z != 0)
			ApplyVelocity(object,object->GetPos(), object->GetVelocity(), Vec3<float>(0, 0, object->GetVelocity().z));



		//For non rotated boxes, we can skip checking for rot vel
		#ifdef ALLIGNED_COLLISIONS
		break;
		#endif // ALLIGNED_COLLISIONS

	//Apply rotational velocity in each direction if doing so wont cause a collision
		if (object->GetRotVelocity().x != 0)
			ApplyRotVelocity(object, object->GetPos(), object->GetRotVelocity(), Vec3<float>(object->GetRotVelocity().x, 0, 0));
		if (object->GetRotVelocity().y != 0)
			ApplyRotVelocity(object, object->GetPos(), object->GetRotVelocity(), Vec3<float>(0, object->GetRotVelocity().y, 0));
		if (object->GetRotVelocity().z != 0)
			ApplyRotVelocity(object, object->GetPos(), object->GetRotVelocity(), Vec3<float>(0, 0, object->GetRotVelocity().z));

	}
}

std::pair <int, bool>  Scene::ApplyVelocity(std::shared_ptr<DisplayableObject>&  object, Vec3<float> posCur, Vec3<float> velCur, Vec3<float> velComponent, int ground)
{
	//Used for recursive collision checks (if enabled)
	static int counter = 0;
	bool collision = false;
	int firstColID = -1;
	//If the object isnt collidable, then skip collision checks and just apply its velocity immeadiatly 
	if (object->IsCollidable())
	{
		//Check for collisions at its predicted position position agaisnt all other objects
		for (int i = 0; i < objects.size(); ++i)
		{

			//If we are only looking for collisions with object's ground object, then skip collision checks with all other objects
			if (ground != -2 && objects[i]->ID != ground)
				continue;

			//Dont want to test for collisions with self
			if (object->ID == objects[i]->ID)
				continue;

			//If the current object in the array is not collidable, then dont check for collisions
			if (!objects[i]->IsCollidable())
				continue;


			//Cull collisions based on distance for performance
			float distToObj = object->GetPos().distanceTo(objects[i]->GetPos());
			if (distToObj >  object->GetBBox().GetLargestDimension() + objects[i]->GetBBox().GetLargestDimension() + 5)
				continue;

			if (CheckCollision(velComponent, Vec3<float>(0, 0, 0), object->GetBBox(), objects[i]->GetBBox()))
			{
				if (!objects[i]->GetBBox().IsTrigger() && !object->GetBBox().IsTrigger())
				{
					//Let the object know a collision has occured and with what
					if (counter == 0)
						object->OnCollide(objects[i]->TAG);
					collision = true;
					firstColID = objects[i]->ID;
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
	}
	if (collision)
		object->SetVelocity(velCur - velComponent);
	else
	{
		//If no collision occured with ground when applying gravity, then we must check for collisions with other objects to see if they are on the same y-plane, and so should be the new ground, thus preventing incorrect  application of velocuty, 
		if (ground != -2)
			return ApplyVelocity(object, posCur, velCur, velComponent);

		object->SetPos(posCur + velComponent);
	}


	//Return straight away to avoid needless recurssion for non collidable objects
	if (!object->IsCollidable())
		return std::pair <int, bool>(firstColID, collision);



	//Attempt to get objects as close to oneanother as possible if determine that an objects velocity would cause a collision. If recurssion is enabled
	if (RecurisveCollisions)
	{
		//If no collision was predicted then no need to do anything
		if (counter == 0 && !collision)
			return std::pair <int, bool>(firstColID, collision);

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
	return std::pair <int, bool>(firstColID, collision);
}

bool Scene::ApplyRotVelocity(std::shared_ptr<DisplayableObject>& object, Vec3<float> posCur, Vec3<float> rotCur, Vec3<float> rotComponent)
{
	//Used for recursive collision checks (if enabled)
	static int counter = 0;
	bool collision = false;

	//If the object isnt collidable, then skip collision checks and just apply its velocity immeadiatly 
	if (object->IsCollidable())
	{
		//Check for collisions at the predicted rotation agaisnt all other objects
		for (int i = 0; i < objects.size(); ++i)
		{
			//Dont want to test for collisions with self
			if (object->ID == objects[i]->ID)
				continue;

			//If the current object in the array is not collidable, then dont check for collisions
			if (!objects[i]->IsCollidable())
				continue;

			//Cull collisions based on distance for performance
			float distToObj = object->GetPos().distanceTo(objects[i]->GetPos());
			if (distToObj >  object->GetBBox().GetLargestDimension() + objects[i]->GetBBox().GetLargestDimension() + 5)
				continue;


			if (CheckCollision(Vec3<float>(0, 0, 0), rotComponent, object->GetBBox(), objects[i]->GetBBox()))
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
	}
	if (collision)
		object->SetRotVelocity(rotCur - rotComponent);
	else
		object->SetOrientation(rotCur + rotComponent);

	//Return straight away to avoid needless recurssion for non collidable objects
	if (!object->IsCollidable())
		return collision;

	//Attempt to get objects as close to oneanother as possible if determine that an objects velocity would cause a collision. If recurssion is enabled
	if (RecurisveCollisions)
	{
		//If no collision was predicted then no need to do anything
		if (counter == 0 && !collision)
			return collision;

		//Otherwise, attempt to recursivley move the object closer to colliding objects
		if (counter < 1)
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
	std::vector<Vec3<float>> indicies1 = obj1.GetIndicies();
	std::vector<Vec3<float>> indicies2 = obj2.GetIndicies();

	//Apply position offset to each vertex
	for(int i = 0; i < indicies1.size(); ++i)
		indicies1[i] = indicies1[i] + posOffset;
	
	//Get the faces of object testing against
	std::vector<BoxFace> faces = obj2.GetFaces(indicies2);
	//Get indicies of object being tested's bbox
	std::vector<Vec3<float>> indicies = indicies1;

	//First iteration checks if any point of the bbox of object being tested is in the volume of the bbox of object testing against.
	//Second object does the inverse
	bool flags[3][8];
	for (int k = 0; k < 2; ++k)
	{
		//For each face pair, 
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

		//For non rotated boxes, we can skip checking for the other object for performance
		#ifdef ALLIGNED_COLLISIONS
		break;
		#endif // ALLIGNED_COLLISIONS


		//Now need to check other way round for next loop iteration
		faces = obj1.GetFaces(indicies1);
		indicies = indicies2;
	}

	return false;
}


bool Scene::CheckCollisions(std::shared_ptr<DisplayableObject>& obj)
{
	//If the object isnt collidable, then skip collision checks 
	if (!obj->IsCollidable())
		return false;

	bool collision = false;

	for (int i = 0; i < objects.size(); ++i)
	{
		//Dont want to test for collisions with self
		if (obj->ID == objects[i]->ID)
			continue;

		//If the current object in the array is not collidable, then dont check for collisions
		if (!objects[i]->IsCollidable())
			continue;

		//Cull collisions based on distance for performance
		float distToObj = obj->GetPos().distanceTo(objects[i]->GetPos());
		if (distToObj >  obj->GetBBox().GetLargestDimension() + objects[i]->GetBBox().GetLargestDimension() + 5)
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
		//If non default tag was supllied, use it to check for self collision
		if (!tag.compare("NULL") && tag.compare(objects[i]->TAG))
			continue;

		//If the current object in the array is not collidable, then dont check for collisions
		if (!objects[i]->IsCollidable())
			continue;

		//Cull collisions based on distance for performance
		float distToObj = bBox.GetParentPos().distanceTo(objects[i]->GetPos());
		if (distToObj >  bBox.GetLargestDimension() + objects[i]->GetBBox().GetLargestDimension() + 5)
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



