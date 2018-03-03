#pragma once
#include <GL/glut.h>
class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Render() = 0;
	//Default empty update. Overide for logic/animations/phsyics etc
	virtual void Update(long tCurrent);

};

