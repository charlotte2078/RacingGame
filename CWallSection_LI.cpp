#include "CWallSection_LI.h"

// Defualt constructor - dont want to use, does nothing
CWallSection_LI::CWallSection_LI()
{
}

CWallSection_LI::CWallSection_LI(Mesh* DummyMesh, Mesh* WallMesh, Mesh* IsleMesh, const CVector2D& Pos, const float& Rot)  :
	CLevelItem(Pos, Rot)
{
	// Create dummy model
	DummyModel = DummyMesh->CreateModel();

	// Loop through walls array
	for (int i = 0; i < NumWalls; i++)
	{
		// Create wall models and attach to dummy
		WallsArr[i] = WallMesh->CreateModel();
		WallsArr[i]->AttachToParent(DummyModel);

		// Move wall models relative Z pos by offset
		if (i == 0)
		{
			WallsArr[i]->MoveLocalZ(-WallOffset);
		}
		else
		{
			WallsArr[i]->MoveLocalZ(WallOffset);
		}
	}
	
	// Loop through isles array
	for (int i = 0; i < NumIsles; i++)
	{
		// Create isle models and attach to dummy
		IslesArr[i] = IsleMesh->CreateModel();
		IslesArr[i]->AttachToParent(DummyModel);

		// Move isle models relative Z pos by offset
		if (i == 0)
		{
			IslesArr[i]->MoveLocalZ(-IsleOffset);
		}
		else if (i == 2)
		{
			IslesArr[i]->MoveLocalZ(IsleOffset);
		}
	}

	// Move dummy model to pos
	DummyModel->SetX(PosXZ.GetX());
	DummyModel->SetZ(PosXZ.GetY());

	// Rotate dummy model by rotation
	DummyModel->RotateY(RotationY);

	// Initialise box collider - to do later!!!!
}

// Does nothing
CWallSection_LI::~CWallSection_LI()
{
}