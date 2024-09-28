#pragma once
#include "CHoverCar.h"

// Global constants for player cars
// Boost constants
const int CarMinHealthForBoost = 30;
const float CarMaxBoostTime = 3.0f;
const float CarBoostMaxMultiplier = 1.5f;
const float CarDragMaxMultiplier = 2.0f;
const float CarMaxThrustMagnitude = 100.0f;
const float CarBoostMaxCooldownTime = 5.0f;
const float CarBoostWarningTime = 1.0f;
const float CarBounceCoefficient = 0.8f;

// Movement constants
const float CarDragCoefficient = 1.5f;

class CHoverCar_Player :
    public CHoverCar
{
private:
	// Boost
	bool CanBoost;				//= true;
	bool IsBoosting;			//= false;
	bool IsBoostCooldown;		//= false;
	float BoostMultiplier;		//= 1.0f;
	float BoostTimer;			//= 0.0f;
	float BoostCooldownTimer;	//= 0.0f;

	// Movement - may need to move some of these to base hover car (lifting and tilting?)
	float DragMultiplier;		//= 1.0f;
	bool IsMovingUp;			//= true;
	float TiltAngle;			//= 0.0f;
	float LiftAngle;			//= 0.0f;

	// Health
	bool IsAlive;				//= true;

	// private methods
	CVector2D CalculateThrust(const float& ThrustFactor);
	CVector2D CalculateDrag();
	void CalculateNewMomentum(const float& DeltaTime, const float& ThrustFactor);
	void MoveByMomentum(const float& DeltaTime);
	//void UpdateFacingVector(); - moved into CHoverCar
	void ProcessBoost(const bool& BoostKeyPress, const float& DeltaTime);
	void Bobble(const float& DeltaTime);
	void ProcessRotation(const bool& LeftKeyPress, const bool& RightKeyPress, const float& DeltaTime);
	void Tilt(const float& DeltaTime, const bool& RightKeyPress, const bool& LeftKeyPress);
	void Lift(const float& DeltaTime, const float& ThrustFactor);
	void CheckHealth();
	void TakeDamage();
	/*void CheckWaypoints();
	void CheckpointCollision(std::vector <SCheckpoint>&, const float&, EGameState&);
	void CheckpointStrutsCollision(std::vector <SCheckpoint>&, const SVector2D&, EGameState&);
	void WallCollision(std::vector <SBoxCollider>&, const SVector2D&, EGameState&);
	void TanksCollision(std::vector <IModel*>, const SVector2D&, EGameState&);
	void NpcCollision(const CNpcCar&, const SVector2D&, EGameState&);
	void TakeDamageCheckEndGame(EGameState&);*/
};

