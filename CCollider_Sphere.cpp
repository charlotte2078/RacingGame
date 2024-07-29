#include "CCollider_Sphere.h"

// Default constructor - sets Radius to 0.0f
CCollider_Sphere::CCollider_Sphere() :
	Radius(0.0f)
{
}

// Constructor with radius passed in
CCollider_Sphere::CCollider_Sphere(const float& Rad) :
	Radius(Rad)
{
}

// Destructor - does nothing
CCollider_Sphere::~CCollider_Sphere()
{
}

void CCollider_Sphere::SetRadius(const float& NewRad)
{
	Radius = NewRad;
}

float CCollider_Sphere::GetRadius() const
{
	return Radius;
}
