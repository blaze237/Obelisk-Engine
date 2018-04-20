#pragma once
#include "DisplayableObject.h"
class Throwable :
	public DisplayableObject
{
public:
	Throwable(Vec3<float> pos, Texture2D tex);
	virtual ~Throwable();

	virtual void Render();
	virtual void OnTrigger(std::string tag);
	virtual bool OnCollide(std::string tag);
	virtual void Update(long tCurrent);
	//Wake the object up and re-enable collisions and rendering
	void Activate(Vec3<float> velocity, Vec3<float> position);

private:

	//Put the object to sleep(disable rendering and collision logic)
	void Deactivate();

	float texTilingX = 1;
	float texTilingZ = 1;
	Texture2D texture;
};

