#pragma once
#include <GL/glut.h>
#include < GL/freeglut.h>
#include <Windows.h>
#include<vector>
#include "Scene.h"
#include "Vec2.h"
#include "Colour.h"
#include <iostream>
#include "Texture2D.h"
#include <exception>
class SceneManager
{
	static const int TICKS_PER_SECOND = 120;
	static const bool showFPS = true;

public:

	//Returns Placeholder texture that can be used if image file cannot be found
	//Have to do this via function as the placeholder generation has to be delayed untill DevIL has been intialised.
	static Texture2D GetErrorTexture()
	{
		if (!DevILInit)
		{
			std::cout << "Error. DevIL image library not intialised. Scene manager must be constructed in order to get error texure!" << std::endl;
			throw std::exception();
		}

		static Texture2D ERROR_TEXTURE = Texture2D("../textures/ERROR.png");

		return ERROR_TEXTURE;
	}

	SceneManager(int argc, char **argv);
	~SceneManager();

	static void AddScene(std::unique_ptr<Scene>);
	
	inline static void SetScene(int index) 
	{
		if (index <= numScenes)
			currentSceneIndex = index;
		else
			std::cout << "Error: Scene index out of bounds!" << std::endl;
	}

	inline static void Exit()
	{
		quit = true;
	}

	//Init glut subsystems and register associated functions
	static void Start();
	//Draw a string to the screen. Specify a position in screen coordinates and an optional color
	static void DrawScreenString(std::string s, Vec2<int> pos, Colour c = Colour(1,1,1,1));

	inline static void SetAmbientLight(Colour c)
	{
		GLfloat global_ambient[] = { c.r, c.b, c.g, c.a };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	}

	inline static void DisableCursor()
	{
		glutSetCursor(GLUT_CURSOR_NONE);
	}

	inline static void EnableCursor()
	{
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	}

	inline static const int& GetScreenW()
	{
		return screenW;
	}
	inline static const int& GetScreenH()
	{
		return screenH;
	}

private:
	//Handle window resizing
	static void Reshape(int w, int h);
	//Main loop for the engine. Handles rendering and logic updates. Calls glutMainLoopEvent() once per cycle to process event data.
	static void MainLoop();
	//Handle error logging
	static void HandleGLError();
	//Render loop. Call render for the current scene
	static void Render();
	//Update loop. This is run at a rate Call update for the current scene ADD TIME DELTA
	static void Update(long tCurrent);





private:
	//Target time for logic updates (60fps)
	const static long logicTimeTarget = 16; 
	//Optional render framerate target (60fps)
	const static long renderTimeTarget = 16;
	static bool capFPS;

	static int screenW, screenH;
	static bool fullScreen;
	static const char* title;

	static std::vector<std::unique_ptr<Scene>> scenes;
	static int currentSceneIndex;
	static int numScenes;

	//Store reference to the time at which program starts. Used for tick calculation
	static long startingTime;
	//Start logic ticks at zero
	static long currentTick;
	//Count the number of frames each interval (1 second)
	static int frameCount;
	static int fps;
	static int frameIntervalEnd;

	//Flag used to indicate that image library is intilazed and ready to use.
	static bool DevILInit;

	static bool quit;
};

