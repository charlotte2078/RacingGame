#include "CCheckpoint_LI.h"

// Default constructor
CCheckpoint_LI::CCheckpoint_LI() :
	CheckpointModel(nullptr)
{
}

// Constructor that creates checkpoint at position and rotation with sunken cross.
CCheckpoint_LI::CCheckpoint_LI(Mesh* CPMesh, const Vector2D& CPPos, const float& CPRot, Mesh* CrossMesh, Mesh* DummyMesh) :
	CLevelItem(CPPos, CPRot),	// initialise position and rotation
	CheckpointCross(CrossMesh),	// create cross
	TriggerZone({CpWidth, CpDepth}, DummyMesh)
{
	/*IModel* CheckpointModel;
	CVector2D StrutsPos[NumStrutsPerCheckpoint];
	CCross CheckpointCross;
	CCollider_Box TriggerZone;*/

	// Create checpoint model at correct position. Attach the Box collider to the Model. Then rotate.
	CheckpointModel = CPMesh->CreateModel(PosXZ.X, 0.0f, PosXZ.Y);
	TriggerZone.AttachToBase(CheckpointModel);
	CheckpointModel->RotateY(CPRot);

	// Attach cross to checkpoint and hide it
	CheckpointCross.AttachToCheckpoint(CheckpointModel);
	CheckpointCross.MoveToHiddenHeight();
}

CCollider_Box CCheckpoint_LI::GetTriggerZone()
{
	return TriggerZone;
}

// Makes the checkpoint's cross appear and starts its life timer.
void CCheckpoint_LI::MakeCrossAppear()
{
	CheckpointCross.SetLifeTimer(CrossLifeTimer);
	CheckpointCross.MoveToVisibleHeight();
}


