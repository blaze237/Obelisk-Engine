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
#include "BoundingBox.h"
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

	//Set the global gravity value for the scene
	inline void SetGravity(float g)
	{
		gravity = g;
	}
	//Set the global gravity value for the scene
	inline void SetFriction(float f)
	{
		friction = f;
	}
	//Enable or disable recursive collision checking to get objects as close to each other as possible
	inline void SetRecursiveCollisions(bool b)
	{
		RecurisveCollisions = b;
	}

	//Get the global gravity value for the scene
	inline float GetGravity() const
	{
		return gravity;
	}
	//Get the global friction value for the scene
	inline float GetFriction() const
	{
		return friction;
	}

	inline bool IsRecursiveCollisions() const
	{
		return RecurisveCollisions;
	}

	//Check if a supplied bounding box intersects the boudning box of any object in the scene. Will call OnCollision / onTrigger of the object(s) the supplied bbox interssects. 
	//Self collision checking is available by optionaly supplying the tag of the object the supplied bbox belongs to.
	bool CheckCollisions(BoundingBox bBox, std::string tag = std::string("NULL"), bool multiObjectCollissions = false);


private:
	

	//Update pshysics for all objects (i.e, update position according to velocity, friction and collisions)
	void PhysicsUpdate();

	//Checks if applying an objects velocity in a given direction (given by the velComponent input. For x velocity, would pass (v.x, 0, 0) for velComponent) to its position would cause a collision, and if so, calls the appropriate collision handler and prevents movement by setting the objects velocity to zero.
	//Returns pair of tag of the first thing it collided against, if any, and bool indicating if collision occured. This return is usefull for easily setting an objects grounded status
	std::pair <int, bool> ApplyVelocity(std::shared_ptr<DisplayableObject>&  object, Vec3<float> posCur, Vec3<float> velCur, Vec3<float> velComponent, int ground = -2);
	//Checks if applying an objects rotational velocity in a given axis ((given by the velComponent input. For x velocity, would pass (v.x, 0, 0) for velComponent) to its orientation would cause a collision, and if so, calls the appropriate collision handler and prevents movement by setting the objects rotational velocity to zero.
	bool ApplyRotVelocity(std::shared_ptr<DisplayableObject>&  object, Vec3<float> posCur, Vec3<float> velCur, Vec3<float> velComponent);
	//Check if an object, obj1 collides with an object, obj2, when some positional offset posOffset and rotational offset rotOffsetis applied to obj1's position and orientation.
	bool CheckCollision(Vec3<float> posOffset, Vec3<float> rotOffset, BoundingBox obj1, const BoundingBox obj2);
	//Used for doing collision checks only (i.e, no velocity logic applied) on non-kinematic objects. 
	bool CheckCollisions(std::shared_ptr<DisplayableObject>& obj);


	//Determine if a point is in front of or behind a plane (defined by a point on the plane and the planes normal). Used for collision checking
	bool HalfSpaceTest(Vec3<float> normal, Vec3<float> planePoint, Vec3<float> point);

	//Global Gravity
	float gravity = 0.8f;
	//Global Friction
	float friction = 0.1f;

	//If set to true, when an object is determined to be about to collide with another due to its velocity, the phsyics system will, instead of stopping the object in its tracks, attempt to recursivley find a short distance that can be traveresed without colliding in order to place the objects close but not touching
	//Can have big effect on performance, and similar effect can be acheived more efficently by applying gradualy increasing velocity to objects instead of binary on/off velocity.
	bool RecurisveCollisions = false;
	//What factor to divide the objects velocity by when trying to find shortest distance
	float RecursiveCollisionsFactor = 10.f;
	//How many times to try finding shortest distance before giving up
	int RecursiveCollisionsLimit = 1;
	//Wether to use recursive collisions for collisions resulting from y velocity. Largley uneeded due to the fact that gravity is allready increasingly applied anyway
	bool RecursiveCollisionsForY = false;


protected:
	std::vector<std::shared_ptr<DisplayableObject>> objects;
	std::vector<std::shared_ptr<Light>> lights;

	//The main view cam for the scene
	std::unique_ptr<Camera> mainCam;

	//The current skybox object for this scene
	std::unique_ptr<SkyBox> skyBox;

	
};

