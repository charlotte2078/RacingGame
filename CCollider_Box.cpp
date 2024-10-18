#include "CCollider_Box.h"
#include "CCollider_Sphere.h"

// Moves corners to their correct local position. Corner models must already
// be created and attached to the centre dummy.
void CCollider_Box::MoveCornerPositions()
{
	// 0 = top left; 1 = top right; 2 = bottom left; 3 = bottom right
	CornersArray[0]->SetLocalX(-HalfWidthDepth.GetX());
	CornersArray[0]->SetLocalZ(HalfWidthDepth.GetY());

	CornersArray[1]->SetLocalX(HalfWidthDepth.GetX());
	CornersArray[1]->SetLocalZ(HalfWidthDepth.GetY());

	CornersArray[2]->SetLocalX(-HalfWidthDepth.GetX());
	CornersArray[2]->SetLocalZ(-HalfWidthDepth.GetY());

	CornersArray[3]->SetLocalX(HalfWidthDepth.GetX());
	CornersArray[3]->SetLocalZ(-HalfWidthDepth.GetY());
}

// Update the corners array with current corner positions.
void CCollider_Box::UpdateCornersPosition()
{
	if (HasMoved)
	{
		UpdateCentrePosition();

		for (int i = 0; i < NumBoxCorners; i++)
		{
			CornersPositionArray[i].SetX(CornersArray[i]->GetX());
			CornersPositionArray[i].SetY(CornersArray[i]->GetZ());
		}

		UpdateAxesArray();
	}
}

// Only need to check 2 of the 4 axes for each square, because there are 2 parallel pairs of axes.
// Check the axis perpendicular to top and right sides.
// Top: Corner[1] - Corner[2]
// Right: Corner[2] - Corner[3]
void CCollider_Box::UpdateAxesArray()
{
	for (int i = 0; i < NumBoxAxes; i++)
	{
		AxesArray[i] = CornersPositionArray[i + 1] - CornersPositionArray[i + 2];
	}
}

// Default constructor
CCollider_Box::CCollider_Box()
{
	for (int i = 0; i < NumBoxCorners; i++)
	{
		CornersArray[i] = nullptr;
	}
}

// Constructor with WidthDepth and DummyMesh passed in.
CCollider_Box::CCollider_Box(const Vector2D& NewWidthDepth, Mesh* DummyMesh) :
	WidthDepth(NewWidthDepth),
	CCollider(DummyMesh)
{
	// Calculate half width and depth.
	//HalfWidthDepth = NewWD * 0.5f;
	HalfWidthDepth.SetX(0.5f * NewWidthDepth.GetX());
	HalfWidthDepth.SetY(0.5f * NewWidthDepth.GetY());

	for (int i = 0; i < NumBoxCorners; i++)
	{
		// Create corner dummy models, attach to central dummy model, then move to correct local position.
		CornersArray[i] = DummyMesh->CreateModel();
		CornersArray[i]->AttachToParent(ColliderCentre);
	}

	MoveCornerPositions();
}

// Constructor with WidthDepth, DummyMesh, and the object to attach it to passed in.
CCollider_Box::CCollider_Box(const Vector2D& NewWD, Mesh* DummyMesh, Model* BaseObject) :
	WidthDepth(NewWD),
	CCollider(DummyMesh, BaseObject)
{
	// Calculate half width and depth.
	//HalfWidthDepth = NewWD * 0.5f;
	HalfWidthDepth.SetX(0.5f * NewWD.GetX());
	HalfWidthDepth.SetY(0.5f * NewWD.GetY());
	
	for (int i = 0; i < NumBoxCorners; i++)
	{
		// Create corner dummy models, attach to central dummy model, then move to correct local position.
		CornersArray[i] = DummyMesh->CreateModel();
		CornersArray[i]->AttachToParent(ColliderCentre);
	}

	MoveCornerPositions();
}

// Destructor
CCollider_Box::~CCollider_Box()
{
}

void CCollider_Box::SetWidthDepth(const Vector2D& NewWD)
{
	WidthDepth = NewWD;

	// Update half width depth
	HalfWidthDepth = WidthDepth * 0.5f;
}

Vector2D CCollider_Box::GetWidthDepth() const
{
	return WidthDepth;
}

Vector2D CCollider_Box::GetHalfWidthDepth() const
{
	return HalfWidthDepth;
}

// Returns true if the box is colliding with the sphere
bool CCollider_Box::BoxToSphere(const CCollider_Sphere& Sphere) const
{
	// Collision if sphere x and sphere z are within bounds of box + sphere radius.
	const float BoxX = ColliderCentre->GetX();
	const float BoxZ = ColliderCentre->GetZ();
	const float Radius = Sphere.GetRadius();
	const Vector2D SpherePos = Sphere.GetPosition();

	// Calculate XMin and XMax
	const float XMin = BoxX - HalfWidthDepth.GetX() - Radius;
	const float XMax = BoxX + HalfWidthDepth.GetX() + Radius;

	// Calculate ZMin and ZMax
	const float ZMin = BoxZ - HalfWidthDepth.GetY() - Radius;
	const float ZMax = BoxZ + HalfWidthDepth.GetY() + Radius;

	return ((SpherePos.GetX() <= XMax && SpherePos.GetX() >= XMin) && (SpherePos.GetY() <= ZMax && SpherePos.GetY() >= ZMin));
}