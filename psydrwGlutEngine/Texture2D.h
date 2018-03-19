#pragma once
#include <GL/glut.h>
#include <string>
class Texture2D
{
public:



	Texture2D(std::string fName);
	~Texture2D();

	inline GLuint getID() const 
	{
		return texID;
	}

private:
	//The opengl identifier for this texture
	GLuint texID;
};
