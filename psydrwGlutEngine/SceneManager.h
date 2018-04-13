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

	SceneManager(int argc, char **argv, const char* title);
	~SceneManager();

	//Register a scene with the engines internal list of scenes
	static void AddScene(std::unique_ptr<Scene>);
	
	//Tell the engine to load a certain scene
	inline static void SetScene(int index) 
	{
		if (index <= numScenes)
			currentSceneIndex = index;
		else
			std::cout << "Error: Scene index out of bounds!" << std::endl;
	}

	//Advance to the next scene in the engines list of scenes
	inline static void NextScene()
	{
		if (currentSceneIndex < numScenes)
			++currentSceneIndex;
		else
			std::cout << "Error. Allready at end of scene list!" << std::endl;
	}

	//Retreat to previous scene in the engines list of scenes
	inline static void PreviousScene()
	{
		if (currentSceneIndex > 0)
			--currentSceneIndex;
		else
			std::cout << "Error. Allready at start of scene list!" << std::endl;

	}

	//Close the program
	inline static void Exit()
	{
		std::cout << "quit";
		DisableGameMode();
		quit = true;
	}

	//Enable standard full screen mode at native res
	inline static void EnableFullscreen()
	{
		glutFullScreen();
	}

	//Leave standard full screen mode
	inline void DisableFullscreen()
	{
		glutLeaveFullScreen();
	}

	//(Attempt to) Switch GLUT to game mode with requested settings. Format settings as ( width "x" height  ":" bitsPerPixel  "@" videoRate )
	//Note that enabling game mode will cause all opengl hints youve set (fog, lighting etc) to be discared. And so it should be the first thing you do after constructing the scene manager
	inline static void EnableGameMode(const char*settings)
	{
		glutGameModeString(settings);

		if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
		{
			glutEnterGameMode();

			//Register callbacks again
			Init();
		}
		else
			std::cout << "Could not enter game mode." << std::endl;
	}

	//If game mode is currently enabled, disable it
	inline static void DisableGameMode()
	{
		if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE))
			glutLeaveGameMode();
	}

	//Set cursor params
	inline static void SetCursorEnabled(bool b, GLint cursorStyle = GLUT_CURSOR_INHERIT)
	{
		if (!b)
			//Disable the cursor
			glutSetCursor(GLUT_CURSOR_NONE);
		else
			glutSetCursor(cursorStyle);
	}

	inline static void SetFogParams(Colour c, GLint mode, GLint quality, float density, float start, float end)
	{
		GLfloat fogColor[4] = { c.r, c.g, c.b, c.a };
		glFogi(GL_FOG_MODE, mode);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, density);
		glHint(GL_FOG_HINT, quality);
		glFogf(GL_FOG_START, start); 
		glFogf(GL_FOG_END, end); 
	}

	//Toggle fog on and off
	inline static void SetFog(bool b)
	{
		if (b)
			glEnable(GL_FOG);
		else
			glDisable(GL_FOG);
	}

	//Init glut subsystems and register associated functions
	static void Start();
	//Draw a string to the screen. Specify a position in screen coordinates and an optional color
	static void DrawScreenString(std::string s, Vec2<int> pos, Colour c = Colour(1,1,1,1));

	//Set the ambient ligting params for
	inline static void SetAmbientLight(Colour c)
	{
		GLfloat global_ambient[] = { c.r, c.b, c.g, c.a };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
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

	//Register glut callbacks and define opengl context
	static void Init();

	//Empty function placeholder used to register a 'render' method with glut.
	//As we handle rendering manualy, we just pass it a dummy function to make it happy
	static void NullFunct() {}


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

