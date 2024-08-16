#include "CCollider_Sphere.h"

// Default constructor - sets Radius to 0.0f
CCollider_Sphere::CCollider_Sphere() :
	Radius(0.0f),
	CCollider()
{
}

// Constructor with radius passed in
CCollider_Sphere::CCollider_Sphere(const float& NewRadius, Mesh* DummyMesh, Model* BaseObject) :
	Radius(NewRadius),
	CCollider(DummyMesh, BaseObject)
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

// Checks for collisions between two sphere colliders. Returns true if there is a collision.
bool CCollider_Sphere::SphereToSphere(CCollider_Sphere OtherSphere)
{
	// Collision if the distance between two positions is less than the sum of the radii.
	//const float SquareDistance = 

	//const float Distance = PositionXZ.Distance(OtherSphere.PositionXZ);
	//const float RadiiSum = Radius + OtherSphere.Radius;

	return true;
}
