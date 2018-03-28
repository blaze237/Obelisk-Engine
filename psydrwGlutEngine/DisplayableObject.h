#pragma once
#include <GL/glut.h>
#include "Vec3.h"
#include "BoundingBox.h"
#include "Texture2D.h"
class DisplayableObject
{
public:

	const std::string TAG;
	//Uniquley assigned per object ID
	const unsigned int ID;


	DisplayableObject(Vec3<float> pos, Vec3<float> bBoxSize, std::string tag, Texture2D texture);
	virtual ~DisplayableObject();



	//Calls your render function and handles matrix translations needed to draw at the correct position, scale and orientation. 
	//Not intended to be overiden
	void RenderObject();

	//Overide this with your own render code. Dont call directly, is called by RenderObject
	virtual void Render() = 0;
	//Default empty update. Overide for logic/animations/phsyics etc
	virtual void Update(long tCurrent);
	//Collision handler. Default implemnation does nothing on collision.
	virtual void OnCollide(std::string tag);
	//Trigger collision handler. Default does nothing
	virtual void OnTrigger(std::string tag);


	//Getters
	inline Vec3<float> GetPos() const
	{
		return pos;
	}
	inline Vec3<float> GetScale() const
	{
		return scale;
	}
	inline Vec3<float> GetOrientation() const
	{
		return orientation;
	}
	inline Vec3<float> GetVelocity() const
	{
		return velocity;
	}
	inline Vec3<float> GetRotVelocity() const
	{
		return rotVelocity;
	}
	inline bool IsGrounded() const
	{
		return grounded;
	}
	inline const BoundingBox& GetBBox() const
	{
		return bBox;
	}
	inline std::string GetTag() const
	{
		return TAG;
	}
	inline bool IsMultiCollisionMode() const
	{
		return MULTI_COLLISION_MODE;
	}
	inline bool IsKinematic() const
	{
		return IS_KINEMATIC;
	}


	//Setters
	inline void SetPos(const Vec3<float>& p)
	{
		pos = p;
	}
	inline void SetPosX(float p)
	{
		pos.x = p;
	}
	inline void SetPosY(float p)
	{
		pos.y = p;
	}
	inline void SetPosZ(float p)
	{
		pos.z = p;
	}
	inline void SetScale(float s)
	{
		scale.x = scale.y = scale.z = s;
	}
	inline void SetScaleX(float s)
	{
		scale.x = s;
	}
	inline void SetScaleY(float s)
	{
		scale.y = s;
	}
	inline void SetScaleZ(float s)
	{
		scale.z = s;
	}
	inline void SetScale(const Vec3<float>& s)
	{
		scale = s;
	}
	inline void SetOrientation(const Vec3<float>& o)
	{
		orientation = o;
	}
	inline void SetVelocity(const Vec3<float>& v)
	{
		velocity = v;
	}
	inline void SetRotVelocity(const Vec3<float>& v)
	{
		rotVelocity = v;
	}
	inline void SetVelocityX(float v)
	{
		velocity.x = v;
	}
	inline void SetVelocityY(float v)
	{
		velocity.y = v;
	}
	inline void SetVelocityZ(float v)
	{
		velocity.z = v;
	}
	inline void SetRotVelocityX(float v)
	{
		rotVelocity.x = v;
	}
	inline void SetRotVelocityY(float v)
	{
		rotVelocity.y = v;
	}inline void SetRotVelocityZ(float v)
	{
		rotVelocity.z = v;
	}
	inline void SetGrounded(bool b)
	{
		grounded = b;
	}
	inline void SetKinematic(bool b)
	{
		IS_KINEMATIC = b;
	}
	inline void SetMultiCollision(bool b)
	{
		MULTI_COLLISION_MODE = b;
	}
	inline void SetColliderRenderer(bool b)
	{
		renderCollider = b;
	}


protected:
	Vec3<float> pos;
	Vec3<float> scale;
	Vec3<float> orientation;
	Vec3<float> velocity;
	Vec3<float> rotVelocity;
	BoundingBox bBox;
	Texture2D texture;
	bool renderCollider = false;

	//Material properites for object
	float matAmb[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float matDif[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
	float matSpec[4] = { 0, 0, 0, 1 };
	float matEmis[4] = { 0, 0, 0, 1 };
	int   matShin = 0;

	//Is this object currently colliding with something underneath it (determined by wether gravity can be applied without causing a collision)
	bool grounded = false;


	//If true, then all concurent collisions with this object will be passed to its OnCollide function.
	//Only enable if needed as for movement logic we dont care about processing all collisions just one for performance
	bool MULTI_COLLISION_MODE = false;
	//Is this object subject to physics logic (gravity, collisions, friction). Note that other objects can still collide with this object even if this object is not kinematic.
	bool IS_KINEMATIC = false;

	static unsigned int nextID;
};

