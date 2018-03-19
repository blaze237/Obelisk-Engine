#include "Texture2D.h"
#include <il/il.h>
#include <iostream>



//Load in the texture from file system and store on the gpu using opengl
Texture2D::Texture2D(std::string fName)
{
	//In order to free up memory after loading in an image file and passing it to the gpu, we need to generate a texture ID for DevIL to use so that we can discard the image data once it has been loaded
	ILuint readID;
	//Generate an image with unique ID and bind it so that all operations hereon will be done on this image
	ilGenImages(1, &readID);
	ilBindImage(readID);

	//Set the image origin to be the same as used by OpenGL
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	//Attempt to load the image data
	bool success = ilLoadImage((ILstring)fName.c_str());

	if (!success)
	{
		std::cout << "Error Loading Image: " << fName << std::endl;
		
		std::string fType = fName.substr(fName.find_last_of(".") + 1);
		if (fType.compare("bmp") == 0)
			std::cout << "Image type is bmp. Try saving the image without colour space information or convert to alternate format" << std::endl;

		//Free the image 
		ilDeleteImages(1, &readID);
	}



	//Convert image data into byte stream so that opengl can read it
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	//Generate and load images in OpenGL
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Upload texture data to the gpu
	glTexImage2D(GL_TEXTURE_2D, static_cast<GLint>(0), ilGetInteger(IL_IMAGE_FORMAT),
		static_cast<GLsizei>(ilGetInteger(IL_IMAGE_WIDTH)), static_cast<GLsizei>(ilGetInteger(IL_IMAGE_HEIGHT)),
		static_cast<GLint>(0), ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

	//Free the image in DevIL
	ilDeleteImages(1, &readID);

}


Texture2D::~Texture2D()
{
}
