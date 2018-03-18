#include "SceneManager.h"
#include <cstdio>
#include <iostream>
#include <string>    
#include <chrono>
#include <thread>
#include <IL/il.h>
#include "InputManager.h"
std::vector<std::unique_ptr<Scene>> SceneManager::scenes;
int SceneManager::currentSceneIndex = 0;
int SceneManager::numScenes = 0;
int SceneManager::screenH = 800;
int SceneManager::screenW = 800;
bool SceneManager::capFPS = true;
long SceneManager::startingTime = 0;
long SceneManager::currentTick = 0;
int SceneManager::frameCount = 0;
int SceneManager::fps = 0;
int SceneManager::frameIntervalEnd = 0;

SceneManager::SceneManager(int argc, char **argv)
{
	//Init DevIL library
	ilInit();

	//Init glut
	glutInit(&argc, argv);

	//Make the window
	glutInitWindowSize(screenW, screenH);
	glutCreateWindow("INSERT TITLE");

	//Place cursor in center of window
	glutWarpPointer(screenW / 2, screenH / 2);

	//Disable the cursor
	glutSetCursor(GLUT_CURSOR_NONE);

	//Set background colour
	Colour bgCol(0.0f, 0.0f, 0.0f, 0.0f);
	glClearColor(bgCol.r, bgCol.g, bgCol.b, bgCol.a);

	//Enable correct z ordering of object faces. Without this faces must be consturcted in the order we wish them to layer.
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

	glEnable(GL_LIGHTING);

	// Enable smooth shading from lighting
	glShadeModel(GL_SMOOTH);

	// Enable automatic normalisation of normal vectors
	glEnable(GL_NORMALIZE);

	//Register the render function with freeglut. We actualy manage all rendering manualy but freeglut requires us to register a render method in order to function
	glutDisplayFunc(Render);

	//Check and handle any errors
	HandleGLError();

	//Register reshape function to handle window size chnages
	glutReshapeFunc(Reshape);

	//Register key listeners
	glutKeyboardFunc(InputManager::KeyDown);
	glutKeyboardUpFunc(InputManager::KeyUp);
	glutSpecialFunc(InputManager::SpecialKeyDown);
	glutSpecialUpFunc(InputManager::SpecialKeyUp);
	glutMouseFunc(InputManager::MouseButton);
	glutMouseWheelFunc(InputManager::MouseWheelMoved);
	glutMotionFunc(InputManager::MouseDrag);
	glutPassiveMotionFunc(InputManager::MouseMoved);
}


SceneManager::~SceneManager()
{
}

void SceneManager::AddScene(std::unique_ptr<Scene> s)
{
	scenes.push_back(std::move(s));
	++numScenes;
}


void SceneManager::Start()
{
	if (numScenes == 0)
	{
		std::cout << "Error! You must add at least one scene before intialising the engine!" << std::endl;
		return;
	}

	//Get engine start time
	startingTime = glutGet(GLUT_ELAPSED_TIME);

	//Initialise the fps couter interval to be 1 second past start time
	frameIntervalEnd = startingTime + 1000;

	//Start the engine
	MainLoop();
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



void SceneManager::MainLoop()
{
	glutMainLoopEvent();

	//Run the game indefintely till the window is closed via glut
	while (true) 
	{
		//Get start time for this frame
		long fStart = glutGet(GLUT_ELAPSED_TIME);
		//Determine what click we should be at by this time
		long targetTick = ((int)(fStart - startingTime) * TICKS_PER_SECOND) / 1000;

		
		//Continualy update the game untill we reach the target tick
		while (currentTick < targetTick) 
		{
			Update(glutGet(GLUT_ELAPSED_TIME));
			++currentTick;
		}

		//Draw a frame
		Render();

		//Calculate the fps
		++frameCount;
		if (fStart >= frameIntervalEnd)
		{
			fps = frameCount;
			frameCount = 0;
			frameIntervalEnd = fStart + 1000;
		}

		//Max number of visualy different renderable frames is set by the tick rate, therefore we sleep untill the next tick to avoid waisting resources rendering identical intermediate frames
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / TICKS_PER_SECOND + fStart - glutGet(GLUT_ELAPSED_TIME)));
	}
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

	if(showFPS)
		DrawScreenString("FPS: " + std::to_string(fps), Vec2<int>(20,screenH - 30));

	//Prepare for next render
	HandleGLError();
	glutSwapBuffers();
}

void SceneManager::Update(long tCurrent)
{
	//Process window and key events for this tick. Must be first thing in update loop
	glutMainLoopEvent();
	
	scenes[currentSceneIndex]->Update(tCurrent);

	//if (InputManager::Pressed(InputManager::CTRL))
	//	std::cout << "UP" << std::endl;
	

	//Tell the input manager to advance to polling for next tick. Must be last thing in update loop
	InputManager::Update();
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

void SceneManager::DrawScreenString(std::string s, Vec2<int> pos, Colour c)
{
	//Temporarily disable lighting when drawing string to prevent it interfering witht the colour
	glDisable(GL_LIGHTING);

	//Move drawing to origin
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Switch to screen cooridantes and move drawing to origin
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//Switch to otrhonagraphic projection equal to screen szie
	gluOrtho2D(0, screenW, 0, screenH);

	glColor4f(c.r,c.g, c.b, c.a);
	glRasterPos2i(pos.x, pos.y);  

	const unsigned char* txt = (const unsigned char*)s.c_str();
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, txt);

	//Undo changes to the matricies and switch back to modelview mode
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();


	glEnable(GL_LIGHTING);
}
