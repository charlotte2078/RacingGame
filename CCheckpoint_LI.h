#pragma once

#include "CLevelItem.h"
#include "Vector2D.h"
#include "CCross.h"
#include "CCollider_Box.h"
#include <TL-Engine11.h>

using namespace tle;

const int NumStrutsPerCheckpoint = 2;
const float StrutRadius = 1.3f;
const float DistToStrut = 8.56f;
const float CpWidth = 14.52f;
const float CpDepth = 2.6f;

class CCheckpoint_LI :
    public CLevelItem
{
private:
	IModel* CheckpointModel;
	Vector2D StrutsPos[NumStrutsPerCheckpoint];
	CCross CheckpointCross;
	CCollider_Box TriggerZone;
public:
	// Constructors
	CCheckpoint_LI();
	CCheckpoint_LI(Mesh* CPMesh, const Vector2D& CPPos, const float& CPRot, Mesh* CrossMesh, Mesh* DummyMesh);

	// Destructors

	// Getters
	CCollider_Box GetTriggerZone();

	// Other public methods
	void MakeCrossAppear();
};

