#pragma once
#include <vector>
#include "DisplayableObject.h"
#include <GL/glut.h>
#include <Windows.h>
#include <utility>
#include <memory>

class Scene
{
public:
	Scene();
	virtual ~Scene();

	//Render the scene. Default implementation just tells all objects in the scene to render themselves.
	virtual void Render();
	//Update the scene. Default implementation just tells all objects in the scene to update themselves. 
	virtual void Update(long tCurrent);

protected:
	std::vector<std::unique_ptr<DisplayableObject>> objects;
};

