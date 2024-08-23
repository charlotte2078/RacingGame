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
	//// Collision if the point is within the box bounds.
	//const float BoxX = ColliderCentre->GetX();
	//const float BoxZ = ColliderCentre->GetZ();
	//const CVector2D PointPos = Point.GetPosition();

	//// Calculate XMin and XMax
	//const float XMin = BoxX - HalfWidthDepth.GetX();
	//const float XMax = BoxX + HalfWidthDepth.GetX();

	//// Calculate ZMin and ZMax
	//const float ZMin = BoxZ - HalfWidthDepth.GetY();
	//const float ZMax = BoxZ + HalfWidthDepth.GetY();

	// Collision if point is within the box bounds.
	const CVector2D BoxPos = Box.GetPosition();
	const CVector2D PointPos = GetPosition();
	const CVector2D Box

	// Calculate XMin and XMax
	const float XMin

	return false;
}
