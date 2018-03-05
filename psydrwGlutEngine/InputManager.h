#pragma once
#include <unordered_map>
#include "Vec2.h"
#include <GL/glut.h>

namespace InputManager {
	
	//Integer key indentifiers for special and mouse keys. 
	//USE THESE INSTEAD OF THE ONES USED BY GLUT, AS THEY MAY COLLIDE WITH STANDARD KEY IDS
	const int MOUSE_LEFT = -1;
	const int MOUSE_MIDDLE = -2;
	const int MOUSE_RIGHT = -3;
	const int MOUSE_SCROLL_UP = -4;
	const int MOUSE_SCROLL_DOWN = -5;
	const int F1 = -6;
	const int F2 = -7;
	const int F3 = -8;
	const int F4 = -9;
	const int F5 = -10;
	const int F6 = -11;
	const int F7 = -12;
	const int F8 = -13;
	const int F9 = -14;
	const int F10 = -15;
	const int F11 = -16;
	const int F12 = -17;
	const int LEFT = -18;
	const int UP = -19;
	const int RIGHT = -20;
	const int DOWN = -21;
	const int PG_UP = -22;
	const int PG_DWN = -23;
	const int HOME = -24;
	const int END = -25;
	const int INSERT = -26;
	const int SHIFT = -27;
	const int CTRL = -28;
	const int ALT = -29;
	//Escape isnt a special key but no simple way to check it without memorising its ascii code
	const int ESC = 27;
	 

	//Switch over the hashmaps. The input manager works by querying if a button has been pressed relative to the current tick
	void Update();

	//Is the current flag for this input true
	bool IsDown(int key);
	//Was the flag for this key true in the last tick
	bool WasDown(int key);
	//Was the key pressed this tick 
	bool Pressed(int key);
	//Was the key released this tick
	bool Released(int key);
	//Return the current position of the mouse relative to top left of window
	Vec2<int> GetMousePos();
	//Check if an unhandled upwards scroll has occured this frame
	bool HasScrolledUp();
	bool HasScrolledDown();

	//Input listeners
	void KeyDown(unsigned char key, int x, int y);
	void KeyUp(unsigned char key, int x, int y);
	void SpecialKeyDown(int key, int x, int y);
	void SpecialKeyUp(int key, int x, int y);
	void MouseButton(int key, int val, int x, int y);
	void MouseDrag(int x, int y);
	void MouseMoved(int x, int y);
	void MouseWheelMoved(int key, int dir, int x, int y);

}
using namespace InputManager;
