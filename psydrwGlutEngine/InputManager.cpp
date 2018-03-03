#include "InputManager.h"
#include <iostream>

 const std::unordered_map<int, int> InputManager::specialKeyConversions = {
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
const std::unordered_map<int, int> InputManager::mouseKeyConversions = {
	 { GLUT_LEFT_BUTTON, MOUSE_LEFT },
	 { GLUT_MIDDLE_BUTTON, MOUSE_MIDDLE },
	 { GLUT_RIGHT_BUTTON, MOUSE_RIGHT }
 };
bool InputManager::scrolledUp = false;
bool InputManager::scrolledDown = false;
std::unordered_map<int, bool> InputManager::curInputStates;
std::unordered_map<int, bool> InputManager::prevInputStates;
Vec2<int> InputManager::mousePos;

void InputManager::Update()
{
	//Copy the previous current inputs to the prev input map
	prevInputStates = curInputStates;
}

bool InputManager::IsDown(int key)
{
	//If it doesnt exist, just return false. If it does exist, return the value
	auto it = curInputStates.find(key);
	return (it == curInputStates.end()) ? false : it->second;
}

bool InputManager::WasDown(int key)
{
	auto it = prevInputStates.find(key);
	return (it == prevInputStates.end()) ? false : it->second;
}


void InputManager::setCurState(int key, bool state)
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

bool InputManager::Pressed(int key)
{
	return (!WasDown(key) && IsDown(key));
}

bool InputManager::Released(int key)
{
	return WasDown(key) && !IsDown(key);
}

void InputManager::KeyDown(unsigned char key, int x, int y)
{
	setCurState(key, true);

}

void InputManager::KeyUp(unsigned char key, int x, int y)
{
	setCurState(key, false);
}

void InputManager::SpecialKeyDown(int key, int x, int y)
{
	try {
		//Grab our unique alt ID for the special key and set the state value for that to be true
		setCurState(specialKeyConversions.at(key), true);
	}
	catch (...) {
		std::cout << "Error! Unrecognized special key press. This should never happen" << std::endl;
	}
	
}

void InputManager::SpecialKeyUp(int key, int x, int y)
{

	try {
		//Grab our unique alt ID for the special key and set the state value for that to be true
		setCurState(specialKeyConversions.at(key), false);
	}
	catch (...) {
		std::cout << "Error! Unrecognized special key press. This should never happen" << std::endl;
	}
}

void InputManager::MouseButton(int key, int state, int x, int y)
{

	//NEED TO CHECK STATE


	try {
		//Grab our unique alt ID for the mouse key and set the state value for that to be true
		setCurState(mouseKeyConversions.at(key), false);
	}
	catch (...) {
		std::cout << "Error! Unrecognized special key press. This should never happen" << std::endl;
	}
}

void InputManager::MouseMoved(int x, int y)
{
	mousePos.x = x;
	mousePos.y = y;
}

void InputManager::MouseWheelMoved(int key, int dir, int x, int y)
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
