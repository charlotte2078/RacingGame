#include "CCollider.h"

// Update CentrePosition if the collider has moved.
void CCollider::UpdateCentrePosition()
{
	CentrePosition.X = ColliderCentre->GetX();
	CentrePosition.Y = ColliderCentre->GetZ();
}

// Default constructor - do not use
CCollider::CCollider() :
	ColliderCentre(nullptr),
	CentrePosition()
{
}

// Creates the collider dummy
CCollider::CCollider(Mesh* DummyMesh)
{
	ColliderCentre = DummyMesh->CreateModel();
	UpdateCentrePosition();
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
Vector2D CCollider::GetPosition() const
{
	return Vector2D(ColliderCentre->GetX(), ColliderCentre->GetZ());
}

// Attaches the collider to the model passed in.
void CCollider::AttachToBase(Model* BaseModel)
{
	ColliderCentre->AttachToParent(BaseModel);
}


