#include "CCollider_Box.h"
#include "CCollider_Sphere.h"
#include "CollisionData.h"

// Moves corners to their correct local position. Corner models must already
// be created and attached to the centre dummy.
void CCollider_Box::MoveCornerPositions()
{
	// 0 = top left; 1 = top right; 2 = bottom right; 3 = bottom left
	CornersArray[0]->SetLocalX(-HalfWidthDepth.X);
	CornersArray[0]->SetLocalZ(HalfWidthDepth.Y);

	CornersArray[1]->SetLocalX(HalfWidthDepth.X);
	CornersArray[1]->SetLocalZ(HalfWidthDepth.Y);

	CornersArray[2]->SetLocalX(HalfWidthDepth.X);
	CornersArray[2]->SetLocalZ(-HalfWidthDepth.Y);

	CornersArray[3]->SetLocalX(-HalfWidthDepth.X);
	CornersArray[3]->SetLocalZ(-HalfWidthDepth.Y);

	// Set up corners position array
	for (int i = 0; i < NumBoxCorners; i++)
	{
		CornersPositionArray[i].X = CornersArray[i]->GetX();
		CornersPositionArray[i].Y = CornersArray[i]->GetZ();
	}
}

// Update the corners array with current corner positions.
void CCollider_Box::UpdateCornersPosition()
{
	UpdateCentrePosition();

	for (int i = 0; i < NumBoxCorners; i++)
	{
		CornersPositionArray[i].X = CornersArray[i]->GetX();
		CornersPositionArray[i].Y = CornersArray[i]->GetZ();
	}

	UpdateAxesArray();
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
	HalfWidthDepth.X = 0.5f * NewWidthDepth.X;
	HalfWidthDepth.Y = 0.5f * NewWidthDepth.Y;

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
	HalfWidthDepth.X = 0.5f * NewWD.X;
	HalfWidthDepth.Y = 0.5f * NewWD.Y;
	
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
	const float XMin = BoxX - HalfWidthDepth.X - Radius;
	const float XMax = BoxX + HalfWidthDepth.X + Radius;

	// Calculate ZMin and ZMax
	const float ZMin = BoxZ - HalfWidthDepth.Y - Radius;
	const float ZMax = BoxZ + HalfWidthDepth.Y + Radius;

	return ((SpherePos.X <= XMax && SpherePos.X >= XMin) && (SpherePos.Y <= ZMax && SpherePos.Y >= ZMin));
}

bool CCollider_Box::SATBoxToSphere(const CCollider_Sphere& Sphere) const
{
	
	
	return false;
}

bool CCollider_Box::SATBoxToBox(CCollider_Box& OtherBox, CollisionData& ColData)
{
	// Update box positions if necessary
	UpdateCornersPosition();
	OtherBox.UpdateCornersPosition();

	// Check each axis of first box for collision
	for (int i = 0; i < NumBoxAxes; i++)
	{
		if (!CheckCollisionAxisBoxes(AxesArray[i], OtherBox, ColData))
		{
			return false;
		}
	}

	// Check each axis of second box for collision
	for (int i = 0; i < NumBoxAxes; i++)
	{
		if (!OtherBox.CheckCollisionAxisBoxes(AxesArray[i], *this, ColData))
		{
			return false;
		}
	}

	// Must be colliding if reach this point
	// Check that the collision data axis is in the same direction that we want it for resolution
	// Direction for resolution is outwards from the other box
	Vector2D NormalDirection(CentrePosition - OtherBox.CentrePosition);
	if (NormalDirection.DotProduct(ColData.Normal) < 0.0f)
	{
		ColData.Normal.Reverse();
	}

	// Normalise penetration and normal of collision data
	

	return true;
}

Model* CCollider_Box::GetCentre()
{
	return ColliderCentre;
}

bool CCollider_Box::CheckCollisionAxisBoxes(const Vector2D& Axis, CCollider_Box& OtherBox, CollisionData& ColData)
{
	// Get Min/Max points on current axis from each box
	float Min1, Max1, Min2, Max2;
	GetMinMaxVertexOnAxis(Axis, Min1, Max1);
	OtherBox.GetMinMaxVertexOnAxis(Axis, Min2, Max2);

	// Overlap test 
	// First way (A < C AND B > C)
	// Second way (C < A AND D > A)
	if ((Min1 <= Min2 && Max1 >= Min2) || (Min2 <= Min1 && Max2 >= Min1))
	{
		// If they are overlapping, update collision data.
		ColData.UpdateData(Axis, Min1, Max1, Min2, Max2);

		
		/*Vector2D NormalDirection(CentrePosition - OtherBox.CentrePosition);
		if (NormalDirection.DotProduct(Data.mNormal) < 0.0f)
		{
			Data.mNormal.Reverse();
		}*/

		return true;
	}

	return false;
}

void CCollider_Box::GetMinMaxVertexOnAxis(const Vector2D& Axis, float& Min, float& Max)
{
	// Assume initial min/max
	Min = CornersPositionArray[0].DotProduct(Axis);
	Max = Min;

	// Loop through remaining vertices to find min/max
	for (int i = 1; i < NumBoxCorners; i++)
	{
		float Projection = CornersPositionArray[i].DotProduct(Axis);

		if (Projection < Min)
		{
			Min = Projection;
		}

		if (Projection > Max)
		{
			Max = Projection;
		}
	}
}