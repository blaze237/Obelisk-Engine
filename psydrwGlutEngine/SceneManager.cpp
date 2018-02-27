#include "SceneManager.h"
#include "Colour.h"



SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init(int argc, char **argv)
{

	//Init glut
	glutInit(&argc, argv);
	//Init time counter used for rotation of cam
	lastTimeStep = glutGet(GLUT_ELAPSED_TIME);
	
	//Make the window
	glutInitWindowSize(screenW, screenH);
	glutCreateWindow(title);

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
	
	//Check and handle any errors
	HandleGLError();

	//Register reshape function to handle window size chnages
	glutReshapeFunc(Reshape);
	//Start rendering the scene
	glutMainLoop();

}

void SceneManager::Reshape(int w, int h)
{
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
		Update();

		dt -= logicTimeTarget;
	}

	if (timeSinceRender > renderTimeTarget)
	{
		//Render a frame
		Render();
		//See how long it took to render
		timeSinceRender += glutGet(GLUT_ELAPSED_TIME) - lastTimeStep;
	}

}

void SceneManager::HandleGLError()
{
}

void SceneManager::Render()
{
}

void SceneManager::Update()
{
}
