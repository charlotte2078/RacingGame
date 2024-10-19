#include "CTank_LI.h"

// Default constructor
CTank_LI::CTank_LI() :
	TankModel(nullptr),
	SphereCollider()
{
}

// Constructor with tank mesh passed in - creates tank model and sinks it
CTank_LI::CTank_LI(IMesh* TankMesh) :
	SphereCollider()
{
	TankModel = TankMesh->CreateModel();
	TankModel->MoveZ(TankSinkHeight);
}

// Constructor with tank mesh, position, and rotation passed in
// Creates tank model at correct position and sinks it
CTank_LI::CTank_LI(IMesh* TankMesh, const Vector2D& NewPos, const float& NewRot) :
	SphereCollider(),
	CLevelItem(NewPos, NewRot)
{
	TankModel = TankMesh->CreateModel(PosXZ.X, TankSinkHeight, PosXZ.Y);
	TankModel->RotateX(NewRot);
}

// Destructor
CTank_LI::~CTank_LI()
{
}
