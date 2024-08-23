#include "CCollider_Point.h"

// Defualt constructor - do not use.
CCollider_Point::CCollider_Point() :
	CCollider()
{
}

// Create a point constructor and attach it to a base object.
CCollider_Point::CCollider_Point(Mesh* DummyMesh, Model* BaseObject)
{
	ColliderCentre = DummyMesh->CreateModel();
	ColliderCentre->AttachToParent(BaseObject);
}

// Destructor - does nothing
CCollider_Point::~CCollider_Point()
{
}

// Returns true if the point is colliding with the box.
bool CCollider_Point::PointToBox(const CCollider_Box& Box)
{
	// Collision if point is within the box bounds.
	const CVector2D BoxPos = Box.GetPosition();
	const CVector2D PointPos = GetPosition();
	const CVector2D BoxHalfWidthDepth = Box.GetHalfWidthDepth();

	// Calculate XMin and XMax
	const float XMin = BoxPos.GetX() - BoxHalfWidthDepth.GetX();
	const float XMax = BoxPos.GetX() + BoxHalfWidthDepth.GetX();

	// Calculate ZMin and ZMax
	const float ZMin = BoxPos.GetY() - BoxHalfWidthDepth.GetY();
	const float ZMax = BoxPos.GetY() + BoxHalfWidthDepth.GetY();

	return ((PointPos.GetX() <= XMax && PointPos.GetX() >= XMin) && (PointPos.GetY() <= ZMax && PointPos.GetY() >= ZMin));
}
