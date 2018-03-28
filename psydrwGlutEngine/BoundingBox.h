#pragma once
#include "Vec3.h"
#include <vector>
#include "MathHelp.h"
#include "BoxFace.h"
#include <algorithm>
#include <functional>
#include <array>
class BoundingBox
{
public:
	BoundingBox(float width, float height, float depth, const Vec3<float>& parentPos, const Vec3<float>& parentRot, Vec3<float>& parentScale, bool trigger = false);
	~BoundingBox();

	//Use for debugging
	void Render() const;

	//Calculate and return the position of each vertex based on parent position
	std::vector<Vec3<float>> GetIndicies(Vec3<float> posOffset = Vec3<float>(0,0,0), Vec3<float> rotOffset = Vec3<float>(0, 0, 0)) const;
	std::vector<BoxFace> GetFaces(Vec3<float> posOffset = Vec3<float>(0, 0, 0), Vec3<float> rotOffset = Vec3<float>(0,0,0)) const;



	inline float GetLargestDimension() const
	{
		//Get the two largest cardinal dimensions
		std::array<int, 3> dims = { width * parentScale.x, height * parentScale.y, depth * parentScale.z };
		std::sort(dims.begin(), dims.end(), std::greater<int>());

		//Use them with pythagoras to get largest distance to box edge
		return (dims[0] * dims[0] + dims[1] * dims[1]);
	}

	inline bool IsTrigger() const
	{
		return trigger;
	}

	inline void SetTrigger(bool b)
	{
		trigger = b;
	}

	inline Vec3<float> GetParentPos() const
	{
		return parentPos;
	}


public:
	float width, height, depth;
	//Keeps a reference to parent object position so that can use it to determine box wordlspace bounds at any given point.
	const Vec3<float>& parentPos;
	const Vec3<float>& parentRot;
	const Vec3<float>& parentScale;

	//Is this bounding box a trigger or a collider
	bool trigger;
};

