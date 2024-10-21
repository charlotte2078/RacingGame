#pragma once

#include <TL-Engine11.h>
#include <vector>
#include "CCollider_Box.h"

using namespace tle;

// Global car constants
const int CarDefaultHealth = 100;
const float CarDefaultRotationSpeed = 90.0f;
const Vector2D CarDefaultWidthDepth = { 4.461f, 12.922f };
//const float CarDefaultRadius = 3.0f;

// Global car bobble (Up/down in Y direction)
const float CarBobbleMinY = 0.0f;
const float CarBobbleMaxY = 0.3f;
const float CarBobbleSpeed = 0.2f;

// Global car tilt constants (Tilting = leaning as turning)
const float CarTiltSpeed = 3.5f;		// degrees/sec
const float CarTiltReturnSpeed = 5.0f;	// degrees/sec
const float CarTiltLimit = 5.0f;		// degrees

// Global car lift constants (Lifting = pivoting as movement speed picks up)
const float CarLiftSpeed = 8.0f;		// degrees/sec
const float CarLiftReturnSpeed = 4.0f;	// degrees/sec
const float CarLiftUpperLimit = 5.0f;	// degrees
const float CarLiftLowerLimit = -2.0f;	// degrees

class CHoverCar
{
protected: 
	// These don't change
	Model* CarDummy;
	Model* CarModel;
	Vector2D InitialPos;
	float InitialRotation;
	CCollider_Box BoxCollider;

	// These change
	Vector2D FacingVec;
	Vector2D MomentumVec;
	int Health;
	float RotationSpeed;
	int CheckpointCounter;
	int LapCounter;

	// Yet to add
	// std::vector <SWaypoint> mWaypointsVec;
	// int mWaypointCounter;
	// int mCheckpointCounter;
	// int mLapCounter;

	// Protected methods
	void MoveToInitialPosRot();
	// void CheckCurrentWaypoint();
	void UpdateFacingVec();

public:
	// Constructors
	CHoverCar();
	CHoverCar(Mesh* DummyMesh, Mesh* CarMesh, const Vector2D& Pos, const float& Rot);

	// Destructors
	~CHoverCar();

	// Getters

	// Other public methods

//protected:
//	Model* mDummyModel;
//	Model* mModel;
//	CVector2D mInitalPos;
//	float mInitialRotation;
//	CVector2D mFacingVec;
//	CVector2D mMomentumVec;
//	int mHealth;
//	float mRotationSpeed;
//	std::vector <SWaypoint> mWaypointsVec;
//	int mWaypointCounter;
//	int mCheckpointCounter;
//	int mLapCounter;
//
//	// protected methods
//	void CheckCurrentWaypoint();
//	void MoveToInitialPosRot();
//
//public:
//	// constructors
//	CHoverCar();
//	CHoverCar(Mesh*, Mesh*, const CVector2D&, const float&);
//
//	// destructor
//	~CHoverCar();
//
//	// getters
//	Model* GetDummyModel() const { return mDummyModel; };
//	Model* GetModel() const { return mModel; };
//	CVector2D GetMomentumVec() const { return mMomentumVec; };
//	int GetHealth() const { return mHealth; };
//	int GetCheckpointCounter() const { return mCheckpointCounter; };
//	int GetLapCounter() const { return mLapCounter; };
//
//	// other public methods
//	void SetWaypointsVec(const std::vector <SWaypoint>&);
};

