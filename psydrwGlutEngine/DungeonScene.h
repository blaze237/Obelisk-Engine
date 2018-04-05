#pragma once
#include "Scene.h"
class DungeonScene :  public Scene
{
public:
	DungeonScene();
	~DungeonScene();

	virtual void Update(long tCurrent);

};

