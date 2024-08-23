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
	

	return false;
}
