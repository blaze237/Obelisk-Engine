#include "SceneManager.h"
#include "Colour.h"



SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	//Set background colour
	Colour bgCol(0.2f, 0.2f, 0.2f, 0);
	glClearColor(bgCol.r, bgCol.g, bgCol.b, bgCol.a);


}

void SceneManager::Reshape()
{
}

void SceneManager::HandleGLError()
{
}

void SceneManager::Render()
{
}

void SceneManager::Update()
{
}
