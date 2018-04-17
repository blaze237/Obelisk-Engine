#pragma once
#include <type_traits>
#include <cmath>
template <class T>
class Vec3
{
public:

	Vec3(T x, T y, T z)
		: x(x), y(y), z(z)
	{
		static_assert(std::is_arithmetic<T>::value, "Position values must be numeric!");
	}

	Vec3()
		:x(0), y(0), z(0)
	{

	}



	/***OPERATORS ***/

	//Equality operator
	bool operator==(const Vec3 &p2) const
	{
		return this->x == p2.x && this->y == p2.y && this->z == p2.z;
	}

	//Inequality operator
	bool operator!=(const Vec3 &p2) const
	{
		return !(*this == p2);
	}

	//Addition operator
	Vec3 operator+(const Vec3 &p2) const 
	{
		Vec3 tmp;
		tmp.x = this->x + p2.x;
		tmp.y = this->y + p2.y;
		tmp.z = this->z + p2.z;
		return tmp;
	}

	//Subtraction operator
	Vec3 operator-(const Vec3 &p2) const 
	{
		Vec3 tmp;
		tmp.x = this->x - p2.x;
		tmp.y = this->y - p2.y;
		tmp.z = this->z - p2.z;

		return tmp;
	}

	//Numeric division operator
	Vec3 operator/(const T &d) const
	{
		Vec3 tmp;
		tmp.x = this->x / d;
		tmp.y = this->y / d;
		tmp.z = this->z / d;

		return tmp;
	}

	//Numeric multiplication operator
	Vec3 operator*(const T &m) const 
	{
		Vec3 tmp;
		tmp.x = this->x * m;
		tmp.y = this->y * m;
		tmp.z = this->z * m;

		return tmp;
	}
	//Addition assignment operator
	Vec3& operator+=(const Vec3 &p2) 
	{
		this->x += p2.x;
		this->y += p2.y;
		this->z += p2.z;

		return *this;
	}
	//Subtraction assignment operator
	Vec3& operator-=(const Vec3 &p2) 
	{
		this->x -= p2.x;
		this->y -= p2.y;
		this->z -= p2.z;

		return *this;
	}
	//Multiplication assignment operator
	Vec3& operator*=(const T &m) 
	{
		this->x *= m;
		this->y *= m;
		this->z *= m;

		return *this;
	}
	//Division assignment operator
	Vec3& operator/=(const T &d) 
	{
		this->x /= d;
		this->y /= d;
		this->z /= d;

		return *this;
	}

	//Square bracket 
	T operator[](int i)
	{
		if (i == 0)
			return x;
		if (i == 1)
			return y;
		if (i == 2)
			return z;
		else
			throw std::invalid_argument("Please supply an index between 0 and 2");
	}


	/***MEMBER FUNCTIONS***/
	//Returns absolute distance to another point as a double
	double distanceTo(const Vec3<T> &p) const {
		return sqrt(pow((p.x - this->x), 2) + pow((p.y - this->y), 2) + pow(p.z - this->z,2));
	}

	//Returns angle to another point as a double in radians
	double angleTo(const Vec3<T> &p) const {
		T adj = abs(p.x - this->x);
		double hyp = distanceTo(p);

		return acos(adj / hyp);
	}

	//Normalise the vector
	inline void Normalise()
	{
		T mag = getMagnitude();

		x /= mag;
		y /= mag;
		z /= mag;
	}

	//Calculate the cross product of this vector with another
	inline Vec3 CrossProd(const Vec3<T>& v2) const
	{
		Vec3<T> cp;

		cp.x = (y * v2.z) - (z * v2.y);
		cp.y = (z * v2.x) - (x * v2.z);
		cp.z = (x * v2.y) - (y * v2.x);

		return cp;
	}

	//Calculate the dot product of this vector with another
	inline long double DotProd(const Vec3<T> v2) const
	{
		return (x * v2.x) + (y * v2.y) + (z * v2.z);
	}



	/***GETTERS AND SETTERS ***/
	inline T getX() const
	{
		return x;
	}
	inline T getY() const
	{
		return y;
	}
	inline T getZ() const
	{
		return z;
	}
	inline T getMagnitude() const
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
	inline void setX(T xNew) {
		x = xNew;

	}
	inline void  setY(T yNew) {
		y = yNew;
	}
	inline void setZ(T zNew)
	{
		z = zNew;
	}


	T x;
	T y;
	T z;

};

template<class T>
void PrintVector(Vec3<T>v)
{
	std::cout << "X: " << v.x << " Y: " << v.y << "Z: " << v.z << std::endl;
}
