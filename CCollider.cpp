#include "CCollider.h"

// Default constructor
CCollider::CCollider()
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


