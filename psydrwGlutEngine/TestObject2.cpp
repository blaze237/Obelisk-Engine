#include "TestObject2.h"
#include "InputManager.h"
#include <vector>
#include <iostream>
#include <cmath>
Vec3<float> CalcMidpoint(Vec3<float> p1, Vec3<float> p2)
{
	return Vec3<float>((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0, (p1.z + p2.z) / 2.0);
}

bool planeCheck(Vec3<float> normal, Vec3<float> planePoint, Vec3<float> point)
{
	Vec3<float> tmp = point - planePoint;

	float dist = tmp.DotProd(normal);

	if (dist > 0)
		return true;
	else
		return false;
}

TestObject2::TestObject2(Vec3<float> pos, std::unique_ptr<DisplayableObject>& testOb, Texture2D texture)
	:TestObject(pos, texture), testOb(testOb)
{
}


TestObject2::~TestObject2()
{
}

void TestObject2::Update(long tCurrent)
{
	CheckCollision();

	float speed = 0.25;

	if(InputManager::IsDown(InputManager::LEFT))
		pos.x -=  speed;
	if (InputManager::IsDown(InputManager::RIGHT))
		pos.x += speed;
	if (InputManager::IsDown(InputManager::DOWN))
		pos.y -= speed;
	if (InputManager::IsDown(InputManager::UP))
		pos.y += speed;
}

void TestObject2::CheckCollision()
{
	Vec3<float> midP = CalcMidpoint(pos, Vec3<float>(0, 0, -50));

	Vec3<float> planeNormal = (Vec3<float>(0, 0, -50) - pos);
	planeNormal.Normalise();

	
	bool sideCheck;
	int i = 0;

	std::vector<Vec3<float>> indicies = bBox.GetIndicies();

	for (Vec3<float> p : indicies)
	{
		bool side = planeCheck(planeNormal, midP, p);

		//if(side)
		//	std::cout << side << std::endl;
		
		if (i != 0 && side != sideCheck)
		{
			std::cout << "Collision!" << std::endl;

			return;
		}
		
		sideCheck = side;
		i = 1;
	}

}
