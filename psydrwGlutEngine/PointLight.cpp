#include "PointLight.h"
#include <stdlib.h>    
#include <time.h>     
#include <iostream>
#include "MathHelp.h"

PointLight::PointLight(Vec3<float>pos, Colour ambient, Vec3<int> diffuse, Colour specular)
	:Light(pos, ambient, diffuse, specular, false)
{
	//Set up random number generation
	rng = std::mt19937(seed());
	flickerRange = std::uniform_real_distribution<float>(flickerIntensity /2.f, flickerIntensity);
}



PointLight::~PointLight()
{
}

void PointLight::Render(GLenum lightID)
{
	//DebugRender();
	glEnable(GL_LIGHTING);

	glLightfv(lightID, GL_AMBIENT, amb);
	glLightfv(lightID, GL_DIFFUSE, dif);
	glLightfv(lightID, GL_SPECULAR, spec);
	glLightf(lightID, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(lightID, GL_LINEAR_ATTENUATION, 1.f / (2.f * radius));
	glLightf(lightID, GL_QUADRATIC_ATTENUATION, 1.0f / (2.f * radius * radius));
	glLightfv(lightID, GL_POSITION, pos);


	glEnable(lightID);

}

void PointLight::Update(long tCurrent)
{
	//Break if flickering not enabled
	if (!flicker)
		return;

	//Update timers
	tSinceUpdate += (tCurrent - lastTime);
	lastTime = tCurrent;

	//Break if not enough time passed yet
	if (tSinceUpdate < flickerRate)
		return;
	
	//Reset timer otherwise
	tSinceUpdate = 0;
	//Pick a random flicker offset in the range
	auto offset = flickerRange(rng);
	
	//Apply it to the radius
	radius = MathHelp::Clamp((radius + flickerSign * offset), (radBase - flickerIntensity), (radBase + flickerIntensity));

	//50/50 chance to flip the sign of the offset for the next flicker
	flickerSign = offset > (flickerIntensity*3.f/4.f) ? -1 : 1;

}
