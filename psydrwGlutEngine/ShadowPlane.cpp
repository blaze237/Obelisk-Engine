#include "ShadowPlane.h"





ShadowPlane::ShadowPlane(Vec3<float> pos, Texture2D texture, std::string tag, DisplayableObject & parent, float verticalOffset)
	:PlaneObj(pos, texture, tag, 2), parent(parent), verticalOffset(verticalOffset)
{
}

ShadowPlane::~ShadowPlane()
{
}

void ShadowPlane::Update(long tCurrent)
{
	pos = parent.GetPos();
	pos.y -= verticalOffset;
}
