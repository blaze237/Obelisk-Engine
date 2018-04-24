#include "Target.h"




Target::Target(Vec3<float> pos, Texture2D texture, int& scoreRef, int scoreInc)
	:PlaneObj(pos, texture, "TARGET", 2), scoreRef(scoreRef), scoreInc(scoreInc)
{
}


Target::~Target()
{
}

bool Target::OnCollide(std::string tag)
{
	if (!tag.compare("THROWABLE") && scoreRef < MAX_SCORE)
		scoreRef += scoreInc;
	

	return false;
}
