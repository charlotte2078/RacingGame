#include "CCollider.h"

// Update CentrePosition if the collider has moved.
void CCollider::UpdateCentrePosition()
{
	if (HasMoved)
	{
		CentrePosition.SetX(ColliderCentre->GetX());
		CentrePosition.SetY(ColliderCentre->GetZ());

		HasMoved = false;
	}
}

// Default constructor - do not use
CCollider::CCollider() :
	ColliderCentre(nullptr),
	CentrePosition(),
	HasMoved(false)
{
}

// Creates the collider dummy
CCollider::CCollider(Mesh* DummyMesh)
{
	ColliderCentre = DummyMesh->CreateModel();
	HasMoved = true;
	UpdateCentrePosition();
}

// Creates the collider dummy and attaches it to the base object.
CCollider::CCollider(Mesh* DummyMesh, Model* BaseObject)
{
	ColliderCentre = DummyMesh->CreateModel();
	ColliderCentre->AttachToParent(BaseObject);

	HasMoved = true;
	UpdateCentrePosition();
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


