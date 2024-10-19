#pragma once

#include "Vector2D.h"

class CollisionData
{
public:
	float Penetration;
	Vector2D Normal;

	// Constructors
	CollisionData();

	// Destructors
	~CollisionData();

	// Other functions
	void ResetData();
	void UpdateData(const Vector2D& Axis, const float& Min1, const float& Max1, const float& Min2, const float& Max2);
	void NormaliseData();
};

