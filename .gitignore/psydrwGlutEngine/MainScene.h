//#pragma once
//
//#include <gl/glut.h>                   
//#include <stdio.h>
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <string>
//#include <map>
//
//
//
////How long to wait in ms between each rotation of 1 degree to the camera
//#define timeStep  10
//
////Utility helper struct for passing colour values
//struct Colour {
//	Colour(float r, float g, float b)
//		:r(r), g(g), b(g)
//	{}
//
//	//Colour channel values
//	float r, g, b;
//};
//
////Init opengl and freeglut
//void setup();
////Draw the scene
//void draw();
//int main(int argc, char **argv);
////OpenGL functions
//void checkGLError();
//void reshape(int _width, int _height);
////Draw a cube to the screen with standard vertex winding
//void drawCube(float radius);
////Draw a cube to the screen with inverted vertex winding
//void drawInverseCube(float radius, Colour c);
//void drawTetrahedron(float radius);
//
//
//void cylinder(float h, float r);
////Keep track of how long the program has been running since glut init. Used for setting speed of camera rotation
//long lastDrawTime;
////Window dimensions
//int width, height;
////Counter used for rotating the scene camera
//int theta = 0;
