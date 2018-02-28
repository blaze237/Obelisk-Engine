#pragma once
#include <GL/glut.h>
class DisplayableObject
{
public:
	DisplayableObject();
	~DisplayableObject();

	virtual void Render() = 0;
	virtual void Update(long tCurrent);

};

