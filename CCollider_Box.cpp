#include "CCollider_Box.h"

// Default constructor
CCollider_Box::CCollider_Box()
{
	for (int i = 0; i < NumBoxCorners; i++)
	{
		CornersArray[i] = nullptr;
	}
}

// Constructor with WidthDepth passed in
CCollider_Box::CCollider_Box(const CVector2D& NewWD, Mesh* DummyMesh, Model* BaseObject) :
	WidthDepth(NewWD),
	CCollider(DummyMesh, BaseObject)
{
	// Calculate half width and depth.
	const float HalfWidth = 0.5f * NewWD.GetX();
	const float HalfDepth = 0.5f * NewWD.GetY();
	
	for (int i = 0; i < NumBoxCorners; i++)
	{
		// Create corner dummy models, attach to central dummy model, then move to correct local position.
		CornersArray[i] = DummyMesh->CreateModel();
		CornersArray[i]->AttachToParent(ColliderCentre);

		// 0 = top left; 1 = top right; 2 = bottom left; 3 = bottom right
	}

	// 0 = top left; 1 = top right; 2 = bottom left; 3 = bottom right
	CornersArray[0]->SetLocalX(-HalfWidth);
	CornersArray[0]->SetLocalZ(HalfDepth);

	CornersArray[1]->SetLocalX(HalfWidth);
	CornersArray[1]->SetLocalZ(HalfDepth);

	CornersArray[2]->SetLocalX(-HalfWidth);
	CornersArray[2]->SetLocalZ(-HalfDepth);

	CornersArray[3]->SetLocalX(HalfWidth);
	CornersArray[3]->SetLocalZ(-HalfDepth);
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
