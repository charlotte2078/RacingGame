#pragma once

#include "CVector2D.h"

class CCollider
{
protected:
	CVector2D PositionXZ;

public:
	// Constructors
	CCollider();
	CCollider(const CVector2D&);

	// Setters
	void SetPos(const CVector2D&);

	// Getters
	CVector2D GetPos() const;
};

