#pragma once
#include <GL/glut.h>
#include < GL/freeglut.h>
#include <Windows.h>
#include<vector>
#include "Scene.h"
#include "Vec2.h"
#include "Colour.h"

class SceneManager
{
	static const int TICKS_PER_SECOND = 120;
	static const bool showFPS = true;

public:
	SceneManager();
	~SceneManager();

	static void AddScene(std::unique_ptr<Scene>);
	//Init glut subsystems and register associated functions
	static void Init(int argc, char **argv);
	//Draw a string to the screen. Specify a position in screen coordinates and an optional color
	static void DrawScreenString(std::string s, Vec2<int> pos, Colour c = Colour(1,1,1,1));


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
};

