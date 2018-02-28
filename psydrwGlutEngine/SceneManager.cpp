#include "SceneManager.h"
#include "Colour.h"
#include <cstdio>
#include <iostream>

std::vector<std::unique_ptr<Scene>> SceneManager::scenes;
int SceneManager::currentSceneIndex = 0;
long SceneManager::lastTimeStep = 0;
long SceneManager::timeSinceLogic = 0;
long SceneManager::timeSinceRender = 0;
int SceneManager::screenH = 700;
int SceneManager::screenW = 700;
bool SceneManager::capFPS = true;


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::AddScene(std::unique_ptr<Scene> s)
{
	scenes.push_back(std::move(s));
}


void SceneManager::Init(int argc, char **argv)
{

	//Init glut
	glutInit(&argc, argv);
	//Init time counter used for rotation of cam
	lastTimeStep = glutGet(GLUT_ELAPSED_TIME);
	
	//Make the window
	glutInitWindowSize(screenW, screenH);
	glutCreateWindow("INSERT TITLE");

	//Set background colour
	Colour bgCol(0.0f, 0.0f, 0.0f, 0.0f);
	glClearColor(bgCol.r, bgCol.g, bgCol.b, bgCol.a);

	//Enable correct z ordering of object faces. Without this the cube faces must be consturcted in the order we wish them to layer.
	//With this, opengl handles layering for us by using the components x,y,z values
	glEnable(GL_DEPTH_TEST);

	//Enable backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Enable transparency blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable 2-D texturing
	glEnable(GL_TEXTURE_2D);

	// Enable blending colour information with texture information
	glEnable(GL_COLOR_MATERIAL);

	// Turn off 2 sided lighting
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// set the ambient light model
	GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	// enable directional light lighting
	// (x, y, z, 0.0) -> directional lighting
	// (x, y, z, 1.0) -> positional lighting
	glEnable(GL_LIGHTING);
	GLfloat ambience[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	// Enable smooth shading from lighting
	glShadeModel(GL_SMOOTH);

	// Enable automatic normalisation of normal vectors
	glEnable(GL_NORMALIZE);

	//Register the render function with freeglut
	glutDisplayFunc(Render);

	//Register the idle function with freeglut
	glutIdleFunc(Idle);
	
	//Check and handle any errors
	HandleGLError();

	//Register reshape function to handle window size chnages
	glutReshapeFunc(Reshape);
	//Start rendering the scene
	glutMainLoop();


	lastTimeStep = glutGet(GLUT_ELAPSED_TIME);
	timeSinceLogic = 0;
	timeSinceRender = 0;

}

void SceneManager::Reshape(int w, int h)
{
	// update global dimension variables
	screenW = w;
	screenH = h;
	// calculate new aspect ratio
	GLdouble aspect = static_cast<GLdouble>(screenW) / static_cast<GLdouble>(screenH);

	glMatrixMode(GL_PROJECTION);
	// reset matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, screenW, screenH);

	gluPerspective(45.0, aspect, 1, 1000);
	// return matrix mode to modelling and viewing
	glMatrixMode(GL_MODELVIEW);
}

void SceneManager::Idle()
{
	//Get time since last idle
	timeSinceLogic  += glutGet(GLUT_ELAPSED_TIME) - lastTimeStep;
	timeSinceRender += timeSinceLogic;
	lastTimeStep = glutGet(GLUT_ELAPSED_TIME);

	//If time since last update is greater than update rate, then do logic update(s) till catch up
	long dt = timeSinceLogic;
	while (dt > logicTimeTarget) {
		//Update logic
		Update(lastTimeStep);

		dt -= logicTimeTarget;
	}

	if (capFPS)
	{
		if (timeSinceRender > renderTimeTarget)
		{
			timeSinceRender = 0;
			//Render a frame
			Render();
			//See how long it took to render
			timeSinceRender += glutGet(GLUT_ELAPSED_TIME) - lastTimeStep;
		}
	}
	else
		Render();
}

void SceneManager::Render()
{

	//Set up matrix
	// Clear display buffers and get ready for rendering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Render the scene
	scenes[currentSceneIndex]->Render();

	//Prepare for next render
	HandleGLError();
	glutSwapBuffers();
}

void SceneManager::Update(long tCurrent)
{
	scenes[currentSceneIndex]->Update(tCurrent);
}

void SceneManager::HandleGLError()
{
	int e = 0;                      // Error count
	GLenum error = glGetError();    // Get first glError
	while (GL_NO_ERROR != error)    // Loop until no errors found
	{
		e++;
		std::cout << "GL Error" << e << gluErrorString(error) << std::endl;
		error = glGetError();                                  // Get next glError
	}
}

