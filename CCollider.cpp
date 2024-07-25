#include "CCollider.h"

void CCollider::SetPos(const CVector2D& NewPos)
{
	PositionXZ = NewPos;
}

CVector2D CCollider::GetPos() const
{
	return PositionXZ;
}
