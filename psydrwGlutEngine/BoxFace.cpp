#include "BoxFace.h"

BoxFace::BoxFace(Vec3<float> A, Vec3<float> B, Vec3<float> C, std::string tag)
	:A(A), B(B), C(C), tag(tag)
{
	//Calculate the normal vector of the face 
	normal = (B - A).CrossProd(C - A);

	normal.Normalise();
}