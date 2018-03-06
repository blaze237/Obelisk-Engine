#pragma once
#include <vector>
#include "DisplayableObject.h"
#include <GL/glut.h>
#include <Windows.h>
#include <utility>
#include <memory>
#include "Colour.h"
#include "Vec2.h"
#include "Camera.h"
class Scene
{
public:
	Scene(std::unique_ptr<Camera> cam);
	virtual ~Scene();

	//Render the scene. Default implementation just tells all objects in the scene to render themselves.
	virtual void Render();
	//Update the scene. Default implementation just tells all objects in the scene to update themselves. And calls update on the camera
	virtual void Update(long tCurrent);

	//Passthrough function for calling the scenemanagers screen draw function to avoid having to reimplement this in your scenes.
	void DrawScreenString(std::string, Vec2<int> pos, Colour c = Colour(1,1,1,1));

protected:
	std::vector<std::unique_ptr<GameObject>> objects;
	//The main view cam for the scene
	std::unique_ptr<Camera> mainCam;
};

