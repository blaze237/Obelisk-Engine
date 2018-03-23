#include "BoxFace.h"

BoxFace::BoxFace(Vec3<float> A, Vec3<float> B, Vec3<float> C)
	:A(A), B(B), C(C)
{
	//Calculate the normal vector of the face 
	normal = (B - A).CrossProd(C - A);
}