#include "CollisionData.h"
#include <float.h>

// Default constructor - Sets penetration to large value and normal to (0,0)
CollisionData::CollisionData() :
	Penetration(FLT_MAX),
	Normal()
{
}

// Default destructor - does nothing
CollisionData::~CollisionData()
{
}

// Use for resetting data between collision checks
void CollisionData::ResetData()
{
	Penetration = FLT_MAX; // Initialise to a large number so we find correct minimum
	Normal = { 0.0f, 0.0f };
}

// Checks if the new penetration is smaller than the current penetration. If it is, new penetration replaces current penetration.
// Axis is also stored.
// With help from https://youtu.be/SUyG3aV_vpM?si=cCNq6pM6ntW2Tt8
void CollisionData::UpdateData(const Vector2D& Axis, const float& Min1, const float& Max1, const float& Min2, const float& Max2)
{
	float AxisDepth = Max2 - Min1;
	if ((Max1 - Min2) < AxisDepth)
	{
		AxisDepth = Max1 - Min2;
	}

	if (AxisDepth < Penetration)
	{
		Penetration = AxisDepth;
		Normal = Axis;
	}
}

// Ensure penetration and normal are correct for resolution.
void CollisionData::NormaliseData()
{
	const float DivisionFactor = 1.0f / Normal.Magnitude();
	Penetration *= DivisionFactor;
	Normal *= DivisionFactor;
}
