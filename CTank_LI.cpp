#include "CTank_LI.h"

// Default constructor
CTank_LI::CTank_LI() :
	TankModel(nullptr),
	SphereCollider(TankRadius)
{
}

// Constructor with tank mesh passed in - creates tank model and sinks it
CTank_LI::CTank_LI(IMesh* TankMesh) :
	SphereCollider(TankRadius)
{
	TankModel = TankMesh->CreateModel();
	TankModel->MoveZ(TankSinkHeight);
}

// Constructor with tank mesh, position, and rotation passed in
// Creates tank model at correct position and sinks it
CTank_LI::CTank_LI(IMesh* TankMesh, const CVector2D& NewPos, const float& NewRot) :
	SphereCollider(TankRadius),
	CLevelItem(NewPos, NewRot)
{
	TankModel = TankMesh->CreateModel(PosXZ.GetX(), TankSinkHeight, PosXZ.GetY());
	SphereCollider.SetPos(PosXZ);
}

// Destructor
CTank_LI::~CTank_LI()
{
}
