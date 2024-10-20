#include "CCollider_Sphere.h"
#include "CCollider_Box.h"

// Update the axis used for sphere to box SAT collisions.
// Axis to use is from the centre of the circle to the closest point on the
// box. Axis IS normalised at this stage.
void CCollider_Sphere::UpdateAxis(CCollider_Box& Box)
{
	UpdateCentrePosition();

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
	Axis = Axis.Normalise();
}

void CCollider_Sphere::GetMinMaxVertexOnAxisSphere(const Vector2D& Axis, float& Min, float& Max)
{
	Vector2D RadiusAlongAxis = Axis * Radius;

	Vector2D MaxPoint = CentrePosition + RadiusAlongAxis;
	Vector2D MinPoint = CentrePosition - RadiusAlongAxis;

	Max = MaxPoint.DotProduct(Axis);
	Min = MinPoint.DotProduct(Axis);

	// Check values are correct way around, swap if not.
	if (Min > Max)
	{
		float temp = Min;
		Min = Max;
		Max = temp;
	}
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

Model* CCollider_Sphere::GetCentre()
{
	return ColliderCentre;
}

// Checks for collisions between two sphere colliders. Returns true if there is a collision.
bool CCollider_Sphere::SphereToSphere(const CCollider_Sphere& OtherSphere) const
{
	// Collision if the distance between two positions is less than the sum of the radii.
	const float SquareDistance = GetPosition().SquareDistance(OtherSphere.GetPosition());
	const float RadiiSumSquared = (Radius + OtherSphere.GetRadius()) * (Radius + OtherSphere.GetRadius());

	return SquareDistance < RadiiSumSquared;
}