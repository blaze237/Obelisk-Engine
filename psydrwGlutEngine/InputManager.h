#pragma once
#include <utility>
#include <memory>
#include <unordered_map>
#include "Vec2.h"
#include <GL/glut.h>

class InputManager
{
public:

	//Integer key indentifiers for special and mouse keys. 
	//USE THESE INSTEAD OF THE ONES USED BY GLUT, AS THEY MAY COLLIDE WITH STANDARD KEY IDS
	static const int MOUSE_LEFT= -1;
	static const int MOUSE_MIDDLE = -2;
	static const int MOUSE_RIGHT = -3;
	static const int F1 = -4;
	static const int F2 = -5; 
	static const int F3 = -6;
	static const int F4 = -7;
	static const int F5 = -8;
	static const int F6 = -9;
	static const int F7 = -10;
	static const int F8 = -11;
	static const int F9 = -12;
	static const int F10 = -13;
	static const int F11 = -14;
	static const int F12 = -15;
	static const int LEFT = -16;
	static const int UP = -17;
	static const int RIGHT = -18;
	static const int DOWN = -19;
	static const int PG_UP = -20;
	static const int PG_DWN = -21;
	static const int HOME = -22;
	static const int END = -23;
	static const int INSERT = -24;

private:
	//To make things simpler, we wish to store data on special keys, standard keys and mouse keys all in one hastable. However, each is identified using different types, to get around this, we convert all identifiers to a common identifier system, integers
	//Standard keyboard keys will map to positive integers, and so we use negative values for special keys and mouse keys.
	static const std::unordered_map<int, int> specialKeyConversions;
	static const std::unordered_map<int, int> mouseKeyConversions;

	//Hashtable of state of all inputs 
	static std::unordered_map<int, bool> curInputStates;
	static std::unordered_map<int, bool> prevInputStates;

	//Current mouse position
	static Vec2<int> mousePos;

	//Mouse wheel flags
	static bool scrolledUp;
	static bool scrolledDown;

	//Disable instantiation 
	InputManager() {}
	//Set the corresponding value in the hashtable for the given key to be true or false
	static void setCurState(int key, bool state);



public:

	static InputManager& getInstance()
	{
		//Static function, so input manager is only instantiated the first time
		static InputManager instance;						  
		return instance;
	}
		
	//Disable copy constructor and assignment operator to ensure only ever one instance of the singleton
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

	//Switch over the hashmaps. The input manager works by querying if a button has been pressed relative to the current tick
	static void Update();

	//Is the current flag for this input true
	static bool IsDown(int key);
	//Was the flag for this key true in the last tick
	static bool WasDown(int key);
	//Was the key pressed this tick (and not last tick)
	static bool Pressed(int key);
	static bool Released(int key);

	static inline Vec2<int> GetMousePos() {
		return mousePos;
	}

	static inline bool HasScrolledUp() {
		return scrolledUp;
	}

	static inline bool HasScrolledDown() {
		return scrolledDown;
	}

	//Input listeners
	static void KeyDown(unsigned char key, int x, int y);
	static void KeyUp(unsigned char key, int x, int y);
	static void SpecialKeyDown(int key, int x, int y);
	static void SpecialKeyUp(int key, int x, int y);
	static void MouseButton(int key, int state, int x, int y);
	static void MouseDrag(int x, int y);
	static void MouseMoved(int x, int y);
	static void MouseWheelMoved(int key, int dir, int x, int y);
};

