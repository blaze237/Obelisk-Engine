
#pragma once
#include "AllignedSprite.h"
#include "Camera.h"
class Torch :
	public AllignedSprite
{
public:
	Torch(Vec3<float> pos, Texture2D handleTex, Texture2D sprites, std::string tag, Camera& cam, int nFrames, float frameWidth, long frameRate, Vec3<float> orientation, Vec3<float> flameOffset = Vec3<float>(-0.1, 1.15, 0));
	Torch(Vec3<float> pos, Texture2D handleTex, Texture2D sprites, std::string tag, Camera& cam, int nFrames, float frameWidth, long frameRate, Vec3<float> orientation, float handleTexTiling, Vec3<float> flameOffset = Vec3<float>(-0.1, 1.15, 0));
	Torch(Vec3<float> pos, Texture2D handleTex, Texture2D sprites, std::string tag, Camera& cam, int nFrames, float frameWidth, long frameRate, Vec3<float> orientation, float handleTexTilingX, float handleTexTilingZ, Vec3<float> flameOffset = Vec3<float>(-0.1, 1.15, 0));
	virtual ~Torch();

	inline void SetResolution(float r)
	{
		resolution = r;
	}
	
	//Set the offsets to apply to the position of the flame sprite relative to the handle tip
	inline void SetFlameOffsets(float x, float y,float z)
	{
		fOffsetX = x;
		fOffsetY = y;
		fOffsetZ = z;
	}
	//Flip the sign of the x and z offsets. Usefull for when orientation of handle is flipped 
	inline void FlipFlameOffsets()
	{
		fOffsetX *= -1;
		fOffsetZ *= -1;
	}

	inline float GetResolution() const
	{
		return resolution;
	}


	inline const virtual BoundingBox& GetBBox() const
	{
		return bBoxCust;
	}

	virtual void Render();
	void DrawHandle();

private:
	Texture2D handleTex;
	//Angular resolution used for drawing the handle of the torch
	float resolution = 0.1; //0.5 nice
	float handleTexTilingX = 1;
	float handleTexTilingZ = 1;
	//The orientation of torch in z and x must be fixed at construction to prevent the y-rotation used to align the sprite screwing up the torches bounding box. Hence a custom fixed bbox is used.
	//Changes to the orientation of the torch afterwards will not be represented in the bbox and WILL cause issues with render culling and collisions
	BoundingBox bBoxCust;

	//Offsets to apply to the position of the flame relative to the tip of the handle, Require tweaking depending on the angle you have the torch at for best appearance
	float fOffsetX;
	float fOffsetY;
	float fOffsetZ;
};
