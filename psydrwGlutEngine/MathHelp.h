#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
const double PI = M_PI;

namespace MathHelp
{
	//Clamp a numerical value between two bounds
	template <class T>
	T Clamp(T val, T lb, T ub)
	{
		if (val < lb)
			return lb;
		if (val > ub)
			return ub;

		return val;
	}

	template <class T>
	T ToRadians(T theta)
	{
		return theta * (M_PI / 180.0);
	}

	template <class T>
	T ToDegrees(T theta)
	{
		return theta * (180.0 / M_PI);
	}


	//Get the maximum value from a set of 3
	template <class T>
	T Max3(T i, T j, T k)
	{
		if (i > j && i > k)
			return i;
		if (j > i && j > k)
			return j;
		if (k > i && k > j)
			return k;

		//Equalilty case
		return i;
	}


	//Clamp each axis of a vector between two bounds
	template <class T>
	void Clamp(Vec3<T>& v, T lb, T ub)
	{
		v.x = Clamp<T>(v.x, lb, ub);
		v.y = Clamp<T>(v.y, lb, ub);
		v.z = Clamp<T>(v.z, lb, ub);
	}


	template <class T>
	Vec3<T> RotatePoint(Vec3<T> point, Vec3<T> rotation, bool degrees = true)
	{
		if (degrees)
		{
			rotation.x = ToRadians(rotation.x);
			rotation.y = ToRadians(rotation.y);
			rotation.z = ToRadians(rotation.z);

		}

		//Define and calculate the rotation matricies in each direction
		const double xRot[4][4] = 
		{
			{1, 0, 0, 0},
			{0, cos(rotation.x), -sin(rotation.x), 0},
			{0, sin(rotation.x), cos(rotation.x), 0},
			{0, 0, 0, 1}
		};

		const double yRot[4][4] =
		{
			{cos(rotation.y), 0, sin(rotation.y), 0},
			{0, 1, 0, 0},
			{-sin(rotation.y), 0, cos(rotation.y), 0},
			{0, 0, 0, 1}
		};

		const double zRot[4][4] =
		{
			{cos(rotation.z), -sin(rotation.z), 0, 0},
			{sin(rotation.z), cos(rotation.z), 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		};

		//Convert point into homogoneised matrix
		double hPos[4] = { point.x, point.y, point.z, 1 };

		//Apply each rotation matrix to the point to get new coordiantes.
		//Dont waste time applying matrix for zero rotation
		if (rotation.x != 0)
		{
			double tmp[4] = { 0, 0, 0, 0 };

			//Loop over each row of rotation matrix 
			for (int i = 0; i < 4; ++i)
			{
				//Multiply each element in the row with each element in hPos col to get new position
				for (int j = 0; j < 4; ++j)
				{
					tmp[i] += xRot[i][j] * hPos[j];
				}
			}

			//Set the position value
			for (int i = 0; i < 4; ++i)
				hPos[i] = tmp[i];
		}

		if (rotation.y != 0)
		{

			double tmp[4] = { 0, 0, 0, 0 };

			//Loop over each row of rotation matrix 
			for (int i = 0; i < 4; ++i)
			{
				//Multiply each element in the row with each element in hPos col to get new position
				for (int j = 0; j < 4; ++j)
				{
					tmp[i] += yRot[i][j] * hPos[j];
				}
			}

			//Set the position value
			for (int i = 0; i < 4; ++i)
				hPos[i] = tmp[i];
		}


		if (rotation.z != 0)
		{

			double tmp[4] = { 0, 0, 0, 0 };

			//Loop over each row of rotation matrix 
			for (int i = 0; i < 4; ++i)
			{
				//Multiply each element in the row with each element in hPos col to get new position
				for (int j = 0; j < 4; ++j)
				{
					tmp[i] += zRot[i][j] * hPos[j];
				}
			}

			//Set the position value
			for (int i = 0; i < 4; ++i)
				hPos[i] = tmp[i];
		}
		
		

		


		return Vec3<T>(hPos[0], hPos[1], hPos[2]);
	}




}