#include "CCollider_Sphere.h"

// Update the axis used for sphere to box SAT collisions.
void CCollider_Sphere::UpdateAxis(CCollider_Box& Box)
{
	float MinDist = FLT_MAX;
	int ClosestIndex = -1;

	for (int i = 0; i < NumBoxCorners; i++)
	{
		// Distance between centre and other centre squared
		const float CurrentDist = (Box.CornersPositionArray[i] - this->CentrePosition).SquareMagnitude();

		if (CurrentDist < MinDist)
		{
			MinDist = CurrentDist;
			ClosestIndex = i;
		}
	}

	// Set axis to that of smallest distance
	Axis = Box.CornersPositionArray[ClosestIndex] - this->CentrePosition;
}

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
bool CCollider_Sphere::SphereToSphere(const CCollider_Sphere& OtherSphere) const
{
	// Collision if the distance between two positions is less than the sum of the radii.
	const float SquareDistance = GetPosition().SquareDistance(OtherSphere.GetPosition());
	const float RadiiSumSquared = (Radius + OtherSphere.GetRadius()) * (Radius + OtherSphere.GetRadius());

	return SquareDistance < RadiiSumSquared;
}

// Returns true if the sphere is colliding with the box.
bool CCollider_Sphere::SphereToBox(const CCollider_Box& Box) const
{
	return Box.BoxToSphere(*this);
}

// Returns true if the sphere is colliding with the point.
bool CCollider_Sphere::SphereToPoint(const CCollider_Point& Point) const
{
	return Point.PointToSphere(*this);
}
