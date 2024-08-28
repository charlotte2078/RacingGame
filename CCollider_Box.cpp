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
	//HalfWidthDepth = NewWD * 0.5f;
	HalfWidthDepth.SetX(0.5f * NewWD.GetX());
	HalfWidthDepth.SetY(0.5f * NewWD.GetY());
	
	for (int i = 0; i < NumBoxCorners; i++)
	{
		// Create corner dummy models, attach to central dummy model, then move to correct local position.
		CornersArray[i] = DummyMesh->CreateModel();
		CornersArray[i]->AttachToParent(ColliderCentre);

		// 0 = top left; 1 = top right; 2 = bottom left; 3 = bottom right
	}

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

// Destructor
CCollider_Box::~CCollider_Box()
{
}

void CCollider_Box::SetWidthDepth(const CVector2D& NewWD)
{
	WidthDepth = NewWD;

	// Update half width depth
	HalfWidthDepth = WidthDepth * 0.5f;
}

CVector2D CCollider_Box::GetWidthDepth() const
{
	return WidthDepth;
}

CVector2D CCollider_Box::GetHalfWidthDepth() const
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
	const CVector2D SpherePos = Sphere.GetPosition();

	// Calculate XMin and XMax
	const float XMin = BoxX - HalfWidthDepth.GetX() - Radius;
	const float XMax = BoxX + HalfWidthDepth.GetX() + Radius;

	// Calculate ZMin and ZMax
	const float ZMin = BoxZ - HalfWidthDepth.GetY() - Radius;
	const float ZMax = BoxZ + HalfWidthDepth.GetY() + Radius;

	return ((SpherePos.GetX() <= XMax && SpherePos.GetX() >= XMin) && (SpherePos.GetY() <= ZMax && SpherePos.GetY() >= ZMin));
}

// Returns true if the point is colliding with the box.
bool CCollider_Box::BoxToPoint(const CCollider_Point& Point) const
{
	// Collision if the point is within the box bounds.
	const float BoxX = ColliderCentre->GetX();
	const float BoxZ = ColliderCentre->GetZ();
	const CVector2D PointPos = Point.GetPosition();

	// Calculate XMin and XMax
	const float XMin = BoxX - HalfWidthDepth.GetX();
	const float XMax = BoxX + HalfWidthDepth.GetX();

	// Calculate ZMin and ZMax
	const float ZMin = BoxZ - HalfWidthDepth.GetY();
	const float ZMax = BoxZ + HalfWidthDepth.GetY();
	
	return ((PointPos.GetX() <= XMax && PointPos.GetX() >= XMin) && (PointPos.GetY() <= ZMax && PointPos.GetY() >= ZMin));
}
