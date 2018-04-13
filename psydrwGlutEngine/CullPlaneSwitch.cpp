#include "CullPlaneSwitch.h"
#include "SceneManager.h"

#define cooldown 500

CullPlaneSwitch::CullPlaneSwitch(Vec3<float> pos, std::string tag, CullPlane& cPlane)
	:Cube(pos, tag, SceneManager::GetErrorTexture()), cPlane(cPlane)
{
}


CullPlaneSwitch::~CullPlaneSwitch()
{
}

void CullPlaneSwitch::OnTrigger(std::string tag)
{
	if (curTime - timeTriggered > cooldown)
	{
		cPlane.SetRenderable(!cPlane.IsRenderable());
		timeTriggered = curTime;
	}
}

void CullPlaneSwitch::Update(long tCurrent)
{
	curTime = tCurrent;
}
