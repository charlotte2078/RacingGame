#pragma once

#include <TL-Engine11.h>
#include <vector>
#include "CVector2D.h"

using namespace tle;

// Global car constants
const int CarDefaultHealth = 100;
const float CarDefaultRotationSpeed = 90.0f;

class CHoverCar
{
protected: 
	// These don't change
	Model* CarDummy;
	Model* CarModel;
	CVector2D InitialPos;
	float InitialRotation;

	// These change
	CVector2D FacingVec;
	CVector2D MomentumVec;
	int Health;
	float RotationSpeed;

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
	CHoverCar(Mesh* DummyMesh, Mesh* CarMesh, const CVector2D& Pos, const float& Rot);

	// Destructors

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

