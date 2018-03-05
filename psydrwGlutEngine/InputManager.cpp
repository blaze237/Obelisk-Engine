#include "InputManager.h"
#include <iostream>
#include "Vec3.h"
namespace InputManager
{
	//Use an anonymous namespace to hide internal workings of conversion between glut button IDs and our ID schema
	namespace
	{
		//To make things simpler, we wish to store data on special keys, standard keys and mouse keys all in one hastable. However, each is identified using different types, to get around this, we convert all identifiers to a common identifier system, integers
		//Standard keyboard keys will map to positive integers, and so we use negative values for special keys and mouse keys.
		const std::unordered_map<int, int> specialKeyConversions = {
			{ GLUT_KEY_F1, F1 },
			{ GLUT_KEY_F2, F2 },
			{ GLUT_KEY_F3, F3 },
			{ GLUT_KEY_F4, F4 },
			{ GLUT_KEY_F5, F5 },
			{ GLUT_KEY_F6, F6 },
			{ GLUT_KEY_F7, F7 },
			{ GLUT_KEY_F8, F8 },
			{ GLUT_KEY_F9, F9 },
			{ GLUT_KEY_F10, F10 },
			{ GLUT_KEY_F11, F11 },
			{ GLUT_KEY_F12, F12 },
			{ GLUT_KEY_LEFT, LEFT },
			{ GLUT_KEY_UP, UP },
			{ GLUT_KEY_RIGHT, RIGHT },
			{ GLUT_KEY_DOWN, DOWN },
			{ GLUT_KEY_PAGE_UP, PG_UP },
			{ GLUT_KEY_PAGE_DOWN, PG_DWN },
			{ GLUT_KEY_HOME, HOME },
			{ GLUT_KEY_END, END },
			{ GLUT_KEY_INSERT, INSERT }
		};

		const std::unordered_map<int, int> mouseKeyConversions = {
			{ GLUT_LEFT_BUTTON, MOUSE_LEFT },
			{ GLUT_MIDDLE_BUTTON, MOUSE_MIDDLE },
			{ GLUT_RIGHT_BUTTON, MOUSE_RIGHT },
		};


		//Hashtable of state of all inputs 
		std::unordered_map<int, bool> curInputStates;
		std::unordered_map<int, bool> prevInputStates;

		//Current mouse position
		Vec2<int> mousePos(0,0);

		//Mouse wheel flags
		bool scrolledUp = false;
		bool scrolledDown = false;

		//Set the corresponding value in the hashtable for the given key to be true or false
		void SetCurState(int key, bool state)
		{
			//First we have to check if this key has allready been registered in the current hashtable. 
			auto it = curInputStates.find(key);
			//If it has, simply update its state
			if (it != curInputStates.end())
				it->second = state;
			//Otherwise add it to the table
			else
				curInputStates.emplace(key, state);
		}
	}

	void Update()
	{
		//Copy the previous current inputs to the prev input map
		prevInputStates = curInputStates;

		//Reset the scroll flags
		scrolledDown = scrolledUp = false;
	}

	Vec2<int> GetMousePos() {
		return mousePos;
	}

	bool HasScrolledUp() {
		return scrolledUp;
	}

	bool HasScrolledDown() {
		return scrolledDown;
	}

	bool IsDown(int key)
	{
		//If it doesnt exist, just return false. If it does exist, return the value
		auto it = curInputStates.find(key);
		return (it == curInputStates.end()) ? false : it->second;
	}

	bool WasDown(int key)
	{
		auto it = prevInputStates.find(key);
		return (it == prevInputStates.end()) ? false : it->second;
	}


	void setCurState(int key, bool state)
	{
		//First we have to check if this key has allready been registered in the current hashtable. 
		auto it = curInputStates.find(key);
		//If it has, simply update its state
		if (it != curInputStates.end())
			it->second = state;
		//Otherwise add it to the table
		else
			curInputStates.emplace(key, state);
	}

	bool Pressed(int key)
	{
		return (!WasDown(key) && IsDown(key));
	}

	bool Released(int key)
	{
		return WasDown(key) && !IsDown(key);
	}

	void KeyDown(unsigned char key, int x, int y)
	{
		setCurState(key, true);
	}

	void KeyUp(unsigned char key, int x, int y)
	{
		setCurState(key, false);
	}

	void SpecialKeyDown(int key, int x, int y)
	{
		//Due to the way freeglut handles modifier keys we have to manualy check for these	
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		{
			setCurState(SHIFT, true);
			return;
		}
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
		{
			setCurState(CTRL, true);
			return;
		}
		if (glutGetModifiers() == GLUT_ACTIVE_ALT)
		{
			setCurState(ALT, true);
			return;
		}


		try {
			//Grab our unique alt ID for the special key and set the state value for that to be true
			setCurState(specialKeyConversions.at(key), true);
		}
		catch (...) {
			//Ignore non standard keys. No real easy way of handling these with freeglut 
		}
	}

	void SpecialKeyUp(int key, int x, int y)
	{
		//Due to the way freeglut handles modifier keys we have to manualy check for these	
		if (IsDown(SHIFT) && glutGetModifiers() != GLUT_ACTIVE_SHIFT)
		{
			setCurState(SHIFT, false);
			return;
		}
		if (IsDown(CTRL) && glutGetModifiers() != GLUT_ACTIVE_CTRL)
		{
			setCurState(CTRL, false);
			return;
		}
		if (IsDown(ALT) && glutGetModifiers() != GLUT_ACTIVE_ALT)
		{
			setCurState(ALT, false);
			return;
		}

		try {
			//Grab our unique alt ID for the special key and set the state value for that to be true
			setCurState(specialKeyConversions.at(key), false);
		}
		catch (...) {
			//Ignore non standard keys. No real easy way of handling these with freeglut 
		}
	}

	void MouseButton(int key, int val, int x, int y)
	{
		//NEED TO CHECK STATE
		bool state = (val == GLUT_DOWN) ? true : false;

		try {
			//Grab our unique alt ID for the mouse key and set the state value for that to be true
			setCurState(mouseKeyConversions.at(key), state);
		}
		catch (...) {
			//Ignore non standard keys. No real easy way of handling these with freeglut 
		}
	}

	void MouseMoved(int x, int y)
	{
		mousePos.x = x;
		mousePos.y = y;
	}

	void MouseWheelMoved(int key, int dir, int x, int y)
	{
		if (dir > 0)
		{
			scrolledUp = true;
			scrolledDown = false;
		}
		else
		{
			scrolledDown = true;
			scrolledUp = false;
		}
	}
}