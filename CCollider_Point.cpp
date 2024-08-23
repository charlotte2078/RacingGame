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

bool CCollider_Point::PointToBox(const CCollider_Box& Box)
{
	return false;
}
