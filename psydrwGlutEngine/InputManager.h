#pragma once
class InputManager
{
public:
	InputManager();
	~InputManager();

	//Input listeners
	void onKeyDown(unsigned char key, int x, int y);
	void onKeyUp(unsigned char key, int x, int y);
	void onSpecialKeyDown(int key, int x, int y);
	void onSpecialKeyUp(int key, int x, int y);
	void onMouseButton(int button, int state, int x, int y);
	void onMouseDrag(int x, int y);
	void onMouseMoved(int x, int y);
};

