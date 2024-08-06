#include "CCollider_Box.h"

// Default constructor
CCollider_Box::CCollider_Box()
{
}

// Constructor with WidthDepth passed in
CCollider_Box::CCollider_Box(const CVector2D& NewWD) :
	WidthDepth(NewWD)
{
}

// Constructor with WidthDepth and position passed in
CCollider_Box::CCollider_Box(const CVector2D& NewWD, const CVector2D& NewPos) :
	WidthDepth(NewWD),
	CCollider(NewPos)
{
}

// Destructor
CCollider_Box::~CCollider_Box()
{
}

void CCollider_Box::SetWidthDepth(const CVector2D& NewWD)
{
	WidthDepth = NewWD;
}

CVector2D CCollider_Box::GetWidthDepth() const
{
	return WidthDepth;
}
