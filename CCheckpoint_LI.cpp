#include "CCheckpoint_LI.h"

// Default constructor
CCheckpoint_LI::CCheckpoint_LI() :
	CheckpointModel(nullptr)
{
}

// Constructor to use
// Create checpoint model at correct position and rotation.
// Then create cross and attach it to checkpoint.
// Move cross to sunken height.
CCheckpoint_LI::CCheckpoint_LI(Mesh* CPMesh, const CVector2D& CPPos, const float& CPRot, Mesh* CrossMesh) :
	CLevelItem(CPPos, CPRot),
	CheckpointCross(CrossMesh)
{
	/*IModel* CheckpointModel;
	CVector2D StrutsPos[NumStrutsPerCheckpoint];
	CCross CheckpointCross;
	CCollider_Box TriggerZone;*/

	CheckpointModel = CPMesh->CreateModel(PosXZ.GetX(), 0.0f, PosXZ.GetY());
	CheckpointModel->RotateY(CPRot);

	
}


