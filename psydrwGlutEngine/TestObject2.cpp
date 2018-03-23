#include "TestObject2.h"
#include "InputManager.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "MathHelp.h"
#include "BoxFace.h"
Vec3<float> CalcMidpoint(Vec3<float> p1, Vec3<float> p2)
{
	return Vec3<float>((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0, (p1.z + p2.z) / 2.0);
}

bool BehindPlane(Vec3<float> normal, Vec3<float> planePoint, Vec3<float> point)
{
	Vec3<float> tmp = point - planePoint;

	float dist = tmp.DotProd(normal);

	if (dist > 0)
		return false;
	else
		return true;
}

TestObject2::TestObject2(Vec3<float> pos, std::shared_ptr<DisplayableObject> testOb, Texture2D texture)
	:TestObject(pos, texture), testOb(testOb)
{
	Vec3<float> planeNormal = (this->testOb->GetPos() - pos);

}


TestObject2::~TestObject2()
{
}

void TestObject2::Update(long tCurrent)
{
	long dt = tCurrent - lastTime;
	if (dt > timeStep && InputManager::IsDown(' '))
	{
		//Get the new rotation of the camera
		theta = theta < (360) ? (theta + dt / timeStep) : 0;
		lastTime = tCurrent;
		orientation.x = MathHelp::Clamp( (float)theta, 0.f, 360.0f);
		orientation.y = MathHelp::Clamp( (float)theta, 0.f, 360.0f);
		orientation.z = MathHelp::Clamp((float)theta, 0.f, 360.0f);

	}

	CheckCollision();

	float speed = 0.25;
	//std::cout << pos.x << std::endl;
	if(InputManager::IsDown(InputManager::LEFT))
		pos.x -=  speed;
	if (InputManager::IsDown(InputManager::RIGHT))
		pos.x += speed;
	if (InputManager::IsDown(InputManager::DOWN))
		pos.y -= speed;
	if (InputManager::IsDown(InputManager::UP))
		pos.y += speed;
	if (InputManager::IsDown('['))
		pos.z += speed;
	if (InputManager::IsDown(']'))
		pos.z -= speed;


}

void TestObject2::CheckCollision()
{

	//Get the faces of other object
	std::vector<BoxFace> faces = testOb->GetBBox().GetFaces();
	//Get indicies of our bbox
	std::vector<Vec3<float>> indicies = bBox.GetIndicies();
	int inVol = 0;

	bool flags[3][8];

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
		else
			std::cout << std::endl;

	}
}

