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
#include "Light.h"
#include "SkyBox.h"
#include "MathHelp.h"
class Scene
{
	//Array of light ID's used for light culling
	 const GLenum LIGHT_IDS[8] = {
		GL_LIGHT0,
		GL_LIGHT1,
		GL_LIGHT2,
		GL_LIGHT3,
		GL_LIGHT4,
		GL_LIGHT5,
		GL_LIGHT6,
		GL_LIGHT7
	};
public:
	Scene();
	virtual ~Scene();

	//Render the scene. Default implementation just tells all objects in the scene to render themselves.
	virtual void Render();
	//Update the scene. Default implementation just tells all objects in the scene to update themselves. And calls update on the camera
	virtual void Update(long tCurrent);

	//Render the skybox at main cam position
	void RenderSky();

	//Passthrough function for calling the scenemanagers screen draw function to avoid having to reimplement this in your scenes.
	void DrawScreenString(std::string, Vec2<int> pos, Colour c = Colour(1,1,1,1));

	inline void HandleReshape(int w, int h)
	{
		mainCam->HandleReshape(w, h);
	}
	//Pass rendering duties to a different camera
	inline void SetCam(std::unique_ptr<Camera> cam)
	{
		mainCam = std::move(cam);
	}

	inline void SetSkyBox(std::unique_ptr<SkyBox> sky)
	{
		skyBox = std::move(sky);
	}

private:
	bool LightSortFcn(std::shared_ptr<Light>& a, std::shared_ptr<Light>& b);

protected:
	std::vector<std::shared_ptr<DisplayableObject>> objects;
	std::vector<std::shared_ptr<Light>> lights;

	//The main view cam for the scene
	std::unique_ptr<Camera> mainCam;

	//The current skybox object for this scene
	std::unique_ptr<SkyBox> skyBox;
};

