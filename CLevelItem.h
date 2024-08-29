#pragma once

#include "CVector2D.h"

class CLevelItem
{
protected:
	CVector2D PosXZ;
	float RotationY;

public:
	// constructors
	CLevelItem();
	CLevelItem(const CVector2D& NewPos, const float& NewRot);

	// destructors
	~CLevelItem();

	// setters
	void SetPosition(const CVector2D& NewPos);
	void SetRotationY(const float& NewRot);

	// getters
	CVector2D GetPosition() const;
	float GetRotationY() const;
};

