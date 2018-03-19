#pragma once
#include "DisplayableObject.h"
#include "Texture2D.h"
#include "BoundingBox.h"
#define timeStep  10
class TestObject :
	public DisplayableObject
{
public:
	TestObject(Vec3<float> pos, Texture2D texture = Texture2D(""));
	~TestObject();

	virtual void Render();
	virtual void Update(long tCurrent);
	void drawCube(float radius);

private:
	int theta = 0;
	long lastTime = 0;
	Texture2D texture;
	BoundingBox bBox;
};

