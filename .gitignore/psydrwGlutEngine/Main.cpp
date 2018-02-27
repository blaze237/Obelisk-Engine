



//#include "MainScene.h"
//
//
//void setup()
//{
//	//Setup window
//	width = 800;
//	height = 800;
//	glutInitWindowSize(width, height);
//	glutCreateWindow("Assignment 1");
//
//	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
//	Colour backgroundColour(0.2f, 0.2f, 0.2f);
//
//	//Set background colour
//	glClearColor(backgroundColour.r, backgroundColour.g, backgroundColour.b, 1.0f);
//
//	//Enable correct z ordering of object faces. Without this the cube faces must be consturcted in the order we wish them to layer.
//	//With this, opengl handles layering for us by using the components x,y,z values
//	glEnable(GL_DEPTH_TEST);
//
//	//Enable backface culling
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_BACK);
//                     // add tree to map of strings to DisplayableObjects
//
//	reshape(width, height);
//}
//
//
//void draw()
//{
//	//Get the ellapsed time since the last frame was drawn
//	long dt = glutGet(GLUT_ELAPSED_TIME) - lastDrawTime;
//	//If not enough time has passed, then signal to try again next update and return to avoid needlessly redrawing the scene
//	if (dt < timeStep)
//	{
//		glutPostRedisplay();
//		return;
//	}
//
//	//Get the new rotation of the camera
//	theta = theta < (360) ? ++theta : 0;
//	//Set the drawTime 
//	lastDrawTime = glutGet(GLUT_ELAPSED_TIME);
//
//	//Clear display buffers and get ready for rendering
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	//Set camera position
//	glTranslatef(0.f, 0.f, -50.f);
//	//Slowly rotate the cube
//	glRotatef(theta, 1, 1, 0);
//	glScalef(2.0, 2.0, 2.0);
//	drawTetrahedron(5);
//	// for each pair in the objects map (in this case, one Tree called "tree")
//	// pair is type <string, DisplayableObject*> so must call on 'second' element
//
//	checkGLError();
//	glutSwapBuffers();
//
//	//Signal we want to redraw again next update tick
//	glutPostRedisplay();
//}
//
//void cylinder(float h, float r)
//{
//	float res = 0.1*M_PI;           // resolution (in radians: equivalent to 18 degrees)
//	float x = r, z = 0.f;           // initialise x and z on right of cylinder centre
//	float t = 0.f;                  // initialise angle as 0
//
//	do
//	{
//		glBegin(GL_QUADS);          // new QUAD
//									// Create first points
//		glVertex3f(x, h, z);    // top
//		glVertex3f(x, 0.f, z);  // bottom
//								// Iterate around circle
//		t += res;               // add increment to angle
//		x = r * cos(t);           // move x and z around circle
//		z = r * sin(t);
//		// Close quad
//		glVertex3f(x, 0.f, z);  // bottom
//		glVertex3f(x, h, z);    // top
//		glEnd();                    // end shape
//	} while (t <= 2 * M_PI);        // for a full circle (360 degrees)
//}
//
////Draws a tetrahedron with a given radius
//void drawTetrahedron(float radius)
//{
//	//Begin drawing the tetrahedron
//	glBegin(GL_TRIANGLES);
//
//	//FACE 1
//	glColor3f(1.0f, 0.0f, 0.0f);
//	//Triangle 1
//	glVertex3f(-radius, -radius, radius);
//	glVertex3f(-radius, radius, -radius);
//	glVertex3f(0, -radius, 0);
//	//Triangle 2
//	glVertex3f(0, -radius, 0);
//	glVertex3f(-radius, radius, -radius);
//	glVertex3f(radius, -radius, -radius);
//
//	//FACE 2	
//	glColor3f(0.0f, 1.0f, 0.0f);
//	//Triangle 1
//	glVertex3f(-radius, -radius, radius);
//	glVertex3f(radius, radius, radius);
//	glVertex3f(-radius, 0, 0);
//	//Triangle 2
//	glVertex3f(-radius, 0, 0);
//	glVertex3f(radius, radius, radius);
//	glVertex3f(-radius, radius, -radius);
//
//	//FACE 3	
//	glColor3f(0.0f, 0.0f, 1.0f);
//	//Triangle 1
//	glVertex3f(-radius, radius, -radius);
//	glVertex3f(radius, radius, radius);
//	glVertex3f(0, 0, -radius);
//	//Triangle 2
//	glVertex3f(0, 0, -radius);
//	glVertex3f(radius, radius, radius);
//	glVertex3f(radius, -radius, -radius);
//
//	//FACE 4	
//	glColor3f(1.0f, 0.0f, 1.0f);
//	//Triangle 1
//	glVertex3f(-radius, -radius, radius);
//	glVertex3f(0, -radius, 0);
//	glVertex3f(radius, radius, radius);
//	//Triangle 2
//	glVertex3f(radius, radius, radius);
//	glVertex3f(0, -radius, 0);
//	glVertex3f(radius, -radius, -radius);
//
//
//	glEnd();
//
//}
//
////Draws a standard cube of given radius. By standard, we mean that all its outer faces are defined as such via counter clockwise vertex winding
//void drawCube(float radius)
//{
//	//Start Drawing the cube
//	glBegin(GL_TRIANGLES);
//
//	//FRONT FACE
//	glColor3f(1.0f, 0.0f, 0.0f);
//	//Triangle 1
//	glVertex3f(radius, -radius, radius);
//	glVertex3f(radius, radius, radius);
//	glVertex3f(-radius, radius, radius);
//	//Triangle 2
//	glVertex3f(-radius, radius, radius);
//	glVertex3f(-radius, -radius, radius);
//	glVertex3f(radius, -radius, radius);
//
//	//BACK FACE
//	glColor3f(0.0f, 1.0f, 0.0f);
//	//Triangle 1
//	glVertex3f(radius, -radius, -radius);
//	glVertex3f(-radius, -radius, -radius);
//	glVertex3f(-radius, radius, -radius);
//	//Triangle 2
//	glVertex3f(-radius, radius, -radius);
//	glVertex3f(radius, radius, -radius);
//	glVertex3f(radius, -radius, -radius);
//
//	//TOP FACE
//	glColor3f(0.0f, 0.0f, 1.0f);
//	//Triangle 1
//	glVertex3f(radius, radius, radius);
//	glVertex3f(radius, radius, -radius);
//	glVertex3f(-radius, radius, -radius);
//	//Triangle 2
//	glVertex3f(-radius, radius, -radius);
//	glVertex3f(-radius, radius, radius);
//	glVertex3f(radius, radius, radius);
//
//	//BOTTOM FACE
//	glColor3f(1.0f, 1.0f, 0.0f);
//	//Triangle 1
//	glVertex3f(radius, -radius, radius);
//	glVertex3f(-radius, -radius, radius);
//	glVertex3f(-radius, -radius, -radius);
//	//Triangle 2
//	glVertex3f(-radius, -radius, -radius);
//	glVertex3f(radius, -radius, -radius);
//	glVertex3f(radius, -radius, radius);
//
//	//LEFT FACE 
//	glColor3f(1.0f, 0.0f, 1.0f);
//	//Triangle 1
//	glVertex3f(-radius, -radius, radius);
//	glVertex3f(-radius, radius, radius);
//	glVertex3f(-radius, radius, -radius);
//	//Triangle 2
//	glVertex3f(-radius, radius, -radius);
//	glVertex3f(-radius, -radius, -radius);
//	glVertex3f(-radius, -radius, radius);
//
//	//RIGHT FACE
//	glColor3f(0.0f, 1.0f, 1.0f);
//	//Triangle 1
//	glVertex3f(radius, -radius, radius);
//	glVertex3f(radius, -radius, -radius);
//	glVertex3f(radius, radius, -radius);
//	//Triangle 2
//	glVertex3f(radius, radius, -radius);
//	glVertex3f(radius, radius, radius);
//	glVertex3f(radius, -radius, radius);
//
//	glEnd();
//}
//
////Draws a inverted cube of given radius. By inverted, we mean that all its outer faces are defined back faces via clockwise vertex winding
////Thus allowing the user to see in trough the front facing side of the cube, to see the tetrhedron inside as well as the cubes inner faces
//void drawInverseCube(float radius, Colour col)
//{
//	//Start Drawing the cube
//	glBegin(GL_TRIANGLES);
//	glColor3f(col.r, col.g, col.b);
//
//
//	//FRONT FACE
//	//Triangle 1
//	glVertex3f(-radius, radius, radius);
//	glVertex3f(radius, radius, radius);
//	glVertex3f(radius, -radius, radius);
//	//Triangle 2
//	glVertex3f(radius, -radius, radius);
//	glVertex3f(-radius, -radius, radius);
//	glVertex3f(-radius, radius, radius);
//
//	//BACK FACE
//	//Triangle 1
//	glVertex3f(-radius, radius, -radius);
//	glVertex3f(-radius, -radius, -radius);
//	glVertex3f(radius, -radius, -radius);
//	//Triangle 2
//	glVertex3f(radius, -radius, -radius);
//	glVertex3f(radius, radius, -radius);
//	glVertex3f(-radius, radius, -radius);
//
//	//TOP FACE
//	//Triangle 1
//	glVertex3f(-radius, radius, -radius);
//	glVertex3f(radius, radius, -radius);
//	glVertex3f(radius, radius, radius);
//	//Triangle 2
//	glVertex3f(radius, radius, radius);
//	glVertex3f(-radius, radius, radius);
//	glVertex3f(-radius, radius, -radius);
//
//	//BOTTOM FACE
//	//Triangle 1
//	glVertex3f(-radius, -radius, -radius);
//	glVertex3f(-radius, -radius, radius);
//	glVertex3f(radius, -radius, radius);
//	//Triangle 2
//	glVertex3f(radius, -radius, radius);
//	glVertex3f(radius, -radius, -radius);
//	glVertex3f(-radius, -radius, -radius);
//
//	//LEFT FACE 
//	//Triangle 1
//	glVertex3f(-radius, radius, -radius);
//	glVertex3f(-radius, radius, radius);
//	glVertex3f(-radius, -radius, radius);
//	//Triangle 2
//	glVertex3f(-radius, -radius, radius);
//	glVertex3f(-radius, -radius, -radius);
//	glVertex3f(-radius, radius, -radius);
//
//	//RIGHT FACE
//	//Triangle 1
//	glVertex3f(radius, radius, -radius);
//	glVertex3f(radius, -radius, -radius);
//	glVertex3f(radius, -radius, radius);
//	//Triangle 2
//	glVertex3f(radius, -radius, radius);
//	glVertex3f(radius, radius, radius);
//	glVertex3f(radius, radius, -radius);
//
//
//	glEnd();
//}
//
//
//
//
//
//int main(int argc, char **argv)
//{
//	glutInit(&argc, argv);          // Initialise GL environment
//	lastDrawTime = glutGet(GLUT_ELAPSED_TIME);
//	setup();                        // Call additional initialisation commands
//	glutDisplayFunc(draw);          // Register scene to render contents of draw() function
//	checkGLError();                 // Check any OpenGL errors in initialisation
//	glutReshapeFunc(reshape);
//	glutMainLoop();                 // Begin rendering sequence
//	return 0;
//}
//
//void reshape(int _width, int _height)
//{
//	// update global dimension variables
//	width = _width;
//	height = _height;
//	// calculate new aspect ratio
//	GLdouble aspect = static_cast<GLdouble>(width) / static_cast<GLdouble>(height);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();     // reset matrix
//	gluPerspective(45.0, aspect, 1, 1000);
//	glMatrixMode(GL_MODELVIEW); // return matrix mode to modelling and viewing
//}
//
//void checkGLError()
//{
//	int e = 0;                      // Error count
//	GLenum error = glGetError();    // Get first glError
//	while (GL_NO_ERROR != error)    // Loop until no errors found
//	{
//		e++;
//		printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
//		error = glGetError();                                  // Get next glError
//	}
//}