#pragma once

#include "Vector2D.h"

class CLevelItem
{
protected:
	Vector2D PosXZ;
	float RotationY;

public:
	// constructors
	CLevelItem();
	CLevelItem(const Vector2D& NewPos, const float& NewRot);

	// destructors
	~CLevelItem();

	// setters
	void SetPosition(const Vector2D& NewPos);
	void SetRotationY(const float& NewRot);

	// getters
	Vector2D GetPosition() const;
	float GetRotationY() const;
};

