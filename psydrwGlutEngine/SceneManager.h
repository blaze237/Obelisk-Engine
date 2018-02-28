#pragma once
#include <GL/glut.h>
#include <Windows.h>
#include<vector>
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();



	static void AddScene(std::unique_ptr<Scene>);
	//Init glut subsystems and register associated functions
	static void Init(int argc, char **argv);
	//Handle window resizing
	static void Reshape(int w, int h);
	//Glut idle function. Handles the logic for if its time yet to render a frame or to update phsyics/logic
	static void Idle();
	//Handle error logging
	static void HandleGLError();
	//Render loop. Call render for the current scene
	static void Render();
	//Update loop. Call update for the current scene ADD TIME DELTA
	static void Update(long tCurrent);


private:
	//Target time for logic updates (60fps)
	const static long logicTimeTarget = 16; 
	//Optional render framerate target (60fps)
	const static long renderTimeTarget = 16;
	static bool capFPS;

	static long lastTimeStep, timeSinceLogic, timeSinceRender;
	static int screenW, screenH;
	static bool fullScreen;
	static const char* title;

	static std::vector<std::unique_ptr<Scene>> scenes;
	static int currentSceneIndex;
};

