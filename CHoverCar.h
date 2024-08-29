#pragma once

#include <TL-Engine11.h>
#include <vector>
#include "CVector2D.h"

using namespace tle;

class CHoverCar
{
protected: 
	Model* CarDummy;
	Model* CarModel;
	CVector2D InitialPos;

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

