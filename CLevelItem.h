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
	CLevelItem(const CVector2D&, const float&);

	// destructors
	~CLevelItem();

	// setters
	void SetPosition(const CVector2D&);
	void SetRotationY(const float&);

	// getters
	CVector2D GetPosition() const;
	float GetRotationY() const;
};

