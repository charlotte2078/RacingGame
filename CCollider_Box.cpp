#include "CCollider_Box.h"

void CCollider_Box::SetWidthDepth(const CVector2D& NewWD)
{
	WidthDepth = NewWD;
}

CVector2D CCollider_Box::GetWidthDepth() const
{
	return WidthDepth;
}
