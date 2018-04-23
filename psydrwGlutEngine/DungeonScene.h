#pragma once
#include "Scene.h"
class DungeonScene :  public Scene
{
public:
	DungeonScene();
	~DungeonScene();

	virtual void Update(long tCurrent);
	virtual void Render();


private:
	void CreateSceneGeometry();
	void CreateLights();
	void CreatePlayer();

	//Shared Textures
	Texture2D cobbleTex;
	Texture2D grassTex;
	Texture2D groundTex;
	Texture2D mossRockTex;
	Texture2D bushTex;
	Texture2D flameSprites;

	int score = 0;
};

