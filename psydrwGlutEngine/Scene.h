#pragma once
#include <vector>
#include "DisplayableObject.h"
#include <GL/glut.h>
#include <Windows.h>
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Render() = 0;
	virtual void Update(long tCurrent) = 0;

private:
	std::vector<DisplayableObject*> objects;
};

