#include "TestObject2.h"
#include "InputManager.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "MathHelp.h"
#include "BoxFace.h"

bool BehindPlane(Vec3<float> normal, Vec3<float> planePoint, Vec3<float> point)
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

TestObject2::TestObject2(Vec3<float> pos, std::shared_ptr<DisplayableObject> testOb, Texture2D texture)
	:TestObject(pos, texture, "player"), testOb(testOb)
{
	IS_KINEMATIC = true;
}


TestObject2::~TestObject2()
{
}

void TestObject2::Update(long tCurrent)
{
	long dt = tCurrent - lastTime;
	if (dt > timeStep && InputManager::IsDown('r'))
	{
		//Get the new rotation of the camera
		theta = theta < (360) ? (theta + dt / timeStep) : 0;
		lastTime = tCurrent;
		rotVelocity.x = MathHelp::Clamp( (float)theta, 0.f, 360.0f);
		rotVelocity.y = MathHelp::Clamp( (float)theta, 0.f, 360.0f);
		rotVelocity.z = MathHelp::Clamp((float)theta, 0.f, 360.0f);
		
		
	}

	//CheckCollision();

	float speed = 0.25;
	if (InputManager::IsDown(InputManager::LEFT))
		velocity.x = -speed;
	if (InputManager::IsDown(InputManager::RIGHT))
		velocity.x = speed;
	if (InputManager::IsDown(InputManager::DOWN))
		velocity.z = speed;
	if (InputManager::IsDown(InputManager::UP))
		velocity.z = -speed;
	if (InputManager::Pressed(' '))
		velocity.y += 1.5;






	if(InputManager::Released(InputManager::LEFT) || InputManager::Released(InputManager::RIGHT))
		velocity.x = 0;
	if (InputManager::Released('[') || InputManager::Released(']'))
		velocity.z = 0;
	if (InputManager::Released('r'))
		rotVelocity = Vec3<float>(0, 0, 0);
}

void TestObject2::CheckCollision()
{
	//Get the faces of other object
	std::vector<BoxFace> faces = testOb->GetBBox().GetFaces();
	//Get indicies of our bbox
	std::vector<Vec3<float>> indicies = bBox.GetIndicies();

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
				face1Flags[j] = BehindPlane(face1.normal, face1.A, p);
				++j;
			}
			j = 0;
			//Check each indicie against face1 to see if any are behind it
			for (Vec3<float> p : indicies)
			{
				face2Flags[j] = BehindPlane(face2.normal, face2.A, p);
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
				std::cout << "COLLISION!" << std::endl;
				return;
			}
		}

		//Get the faces of other object
		faces = bBox.GetFaces();
		//Get indicies of our bbox
		indicies = testOb->GetBBox().GetIndicies();
	}

	std::cout << std::endl;

}

