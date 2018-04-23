#include "Throwable.h"



Throwable::Throwable(Vec3<float> pos, Texture2D tex)
	:Sphere(pos, "THROWABLE", tex)
{
	//Trowable will sleep until it is needed
	Deactivate();
}


Throwable::~Throwable()
{
}


void Throwable::OnTrigger(std::string tag)
{
	if (!tag.compare("TARGET"))
		Deactivate();
	

}

bool Throwable::OnCollide(std::string tag)
{
	//We dont want the throwable to collide with the player
	if (!tag.compare("Cam"))
		return true;
	else if (!tag.compare("TARGET"))
	{
		Deactivate();

	}
	return false;
}

void Throwable::Update(long tCurrent)
{

}

void Throwable::Activate(Vec3<float> vel, Vec3<float> position)
{
	collidable = true;
	renderable = true;
	kinematic = true;

	velocity = vel;
	pos = position;
}

void Throwable::Deactivate()
{
	collidable = false;
	renderable = false;
	kinematic = false;
	velocity = Vec3<float>(0, 0, 0);
}
