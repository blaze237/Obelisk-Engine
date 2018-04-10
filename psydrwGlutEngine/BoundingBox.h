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
	std::vector<Vec3<float>> GetIndicies() const;
	std::vector<BoxFace> GetFaces() const;
	std::vector<BoxFace> GetFaces(std::vector<Vec3<float>> ind) const;



	inline float GetLargestDimension() const
	{
		//Check the cached scale values are still valid
		ValidateCache();

		if (dimDirty)
		{
			int dims[3] = { width * parentScale.x, height * parentScale.y, depth * parentScale.z };
			//Use 3D pythagoras to return distance to furthest corner of box
			dimCache =  sqrt(dims[0] * dims[0] + dims[1] * dims[1] + dims[2] * dims[2]);

			dimDirty = false;
		}

		return dimCache;
	}

	//Return the parent scale adjusted dimensions of the bounding box
	inline Vec3<float> GetActualDimensions() const
	{
		return Vec3<float>(width * parentScale.x, height * parentScale.y, depth * parentScale.z);
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
	Vec3<float> offset;
	//Keeps a reference to parent object position so that can use it to determine box wordlspace bounds at any given point.
	const Vec3<float>& parentPos;
	const Vec3<float>& parentRot;
	const Vec3<float>& parentScale;
	//Is this bounding box a trigger or a collider
	bool trigger;

private:
	

	void ValidateCache() const;

	inline void UpdateCache() const
	{
		parentPosCache = parentPos;
		parentRotCache = parentRot;
		parentScaleCache = parentScale;
	}


	
	//Used for caching
	mutable std::vector<Vec3<float>> indiciesCache;
	mutable std::vector<BoxFace> facesCache;
	mutable float dimCache;

	//Used to signal to the box that it needs to recalculate data when asked for it instead of just returning cached versions
	mutable Vec3<float> parentPosCache;
	mutable Vec3<float> parentRotCache;
	mutable Vec3<float> parentScaleCache;
	//Intialy all true as cached data will need to be calculated the first time it is asked for
	mutable bool dimDirty = true;
	mutable bool faceDirty = true;
	mutable bool indDirty = true;
	
};

