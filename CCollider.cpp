#include "CCollider.h"

// Default constructor - do not use
CCollider::CCollider() :
	ColliderCentre(nullptr)
{
}

// Creates the collider dummy and attaches it to the base object.
CCollider::CCollider(Mesh* DummyMesh, Model* BaseObject)
{
	ColliderCentre = DummyMesh->CreateModel();
	ColliderCentre->AttachToParent(BaseObject);
}

// Destructor - does nothing
CCollider::~CCollider()
{
}

// Returns the position of the collider centre (X,Z) as a CVector2D.
CVector2D CCollider::GetPosition() const
{
	return CVector2D(ColliderCentre->GetX(), ColliderCentre->GetZ());
}


