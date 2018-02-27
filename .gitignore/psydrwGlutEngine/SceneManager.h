#pragma once
#include <GL/glut.h>
#include <Windows.h>
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	//Init glut subsystems and register associated functions
	void Init();
	//Handle window resizing
	void Reshape();
	//Handle error logging
	void HandleGLError();
	//Render loop. Call render for the current scene
	void Render();
	//Update loop. Call update for the current scene
	void Update();

private:
	//Target time for logic updates (60fps)
	const static long logicTimeTarget = 16; 
	//Optional render framerate target (60fps)
	const static long frameTimeTarget = 16;
	const static bool capFPS = false;

	int screenW, screenH;
	bool fullScreen;
	const char* title;

};

