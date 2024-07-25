#include "CCollider_Sphere.h"

void CCollider_Sphere::SetRadius(const float& NewRad)
{
	Radius = NewRad;
}

float CCollider_Sphere::GetRadius() const
{
	return Radius;
}
