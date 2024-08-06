#include "CCollider.h"

// Default constructor
CCollider::CCollider()
{
}

// Constructor with position passed in
CCollider::CCollider(const CVector2D& NewPos) :
	PositionXZ(NewPos)
{
}

void CCollider::SetPos(const CVector2D& NewPos)
{
	PositionXZ = NewPos;
}

CVector2D CCollider::GetPos() const
{
	return PositionXZ;
}
