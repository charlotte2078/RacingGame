#include "CLevelItem.h"

// Default constructor - default values (0,0) position and 0.0f rotation
CLevelItem::CLevelItem() :
	PosXZ(),
	RotationY(0.0f)
{
}

// Constructor with parameters passed in
CLevelItem::CLevelItem(const Vector2D& NewPos, const float& NewRot) :
	PosXZ(NewPos),
	RotationY(NewRot)
{
}

// Destructor - does nothing
CLevelItem::~CLevelItem()
{
}

void CLevelItem::SetPosition(const Vector2D& NewPos)
{
	PosXZ = NewPos;
}

void CLevelItem::SetRotationY(const float& NewRot)
{
	RotationY = NewRot;
}

Vector2D CLevelItem::GetPosition() const
{
	return PosXZ;
}

float CLevelItem::GetRotationY() const
{
	return RotationY;
}