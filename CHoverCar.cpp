#include "CHoverCar.h"

// Moves the car to its initial position and rotation.
void CHoverCar::MoveToInitialPosRot()
{
	// Position
	CarDummy->SetX(InitialPos.X);
	CarDummy->SetZ(InitialPos.Y);
	
	// Rotation
	CarDummy->ResetOrientation();
	CarDummy->RotateY(InitialRotation);
}

// Updates the facing vector for the car
void CHoverCar::UpdateFacingVec()
{
	float matrix[4][4];
	CarDummy->GetMatrix(&matrix[0][0]);
	FacingVec = { matrix[2][0],matrix[2][2] };
}

// Default constructor - do not use
CHoverCar::CHoverCar() :
	CarDummy(nullptr),
	CarModel(nullptr),
	InitialRotation(0.0f),
	Health(CarDefaultHealth),
	RotationSpeed(CarDefaultRotationSpeed),
	InitialPos({0.0f, 0.0f}),
	FacingVec({0.0f, 1.0f}),
	MomentumVec({0.0f, 0.0f}),
	BoxCollider(),
	CheckpointCounter(0),
	LapCounter(0)
{
}

// Constructor with meshes and intial position and rotation passed in.
CHoverCar::CHoverCar(Mesh* DummyMesh, Mesh* CarMesh, const Vector2D& Pos, const float& Rot) :
	InitialPos(Pos),
	InitialRotation(Rot),
	Health(CarDefaultHealth),
	RotationSpeed(CarDefaultRotationSpeed),
	MomentumVec({0.0f, 0.0f}),
	CheckpointCounter(0),
	LapCounter(0)
{
	// Create dummy model in the correct position and rotation
	CarDummy = DummyMesh->CreateModel();
	MoveToInitialPosRot();

	// Create car model and attach it to dummy
	CarModel = CarMesh->CreateModel();
	CarModel->AttachToParent(CarDummy);

	// Initialise the box collider
	BoxCollider = CCollider_Box(CarDefaultWidthDepth, DummyMesh, CarDummy);

	// Calculate Facing Vector
	UpdateFacingVec();
}

// Destructor - does nothing
CHoverCar::~CHoverCar()
{
}
