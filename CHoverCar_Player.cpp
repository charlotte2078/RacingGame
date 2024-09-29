#include "CHoverCar_Player.h"

// Calculates thrust vector for the frame.
CVector2D CHoverCar_Player::CalculateThrust(const float& ThrustFactor)
{
    return (FacingVec * (ThrustFactor * CarMaxThrustMagnitude * BoostMultiplier));
}

// Calculates drag for the frame (in opposite direction to momentum)
CVector2D CHoverCar_Player::CalculateDrag()
{
	return (MomentumVec * (-CarDragCoefficient * DragMultiplier));
}

// Calculates new momentum using resultant force, multiplies force by DeltaTime
void CHoverCar_Player::CalculateNewMomentum(const float& DeltaTime, const float& ThrustFactor)
{
	CVector2D ResultantForce = CalculateDrag() + CalculateThrust(ThrustFactor);
	MomentumVec = (ResultantForce * DeltaTime) + MomentumVec;
}

// Moves the car using its momentum vector multiplied by DeltaTime
void CHoverCar_Player::MoveByMomentum(const float& DeltaTime)
{
	CarDummy->MoveX(MomentumVec.GetX() * DeltaTime);
	CarDummy->MoveZ(MomentumVec.GetY() * DeltaTime);
}

// Changes boost timers and multipliers. If the player can boost and they press the boost key,
// the max. thrust is increased by CarBoostMaxMultiplier. They can only boost for a limited time,
// (determined by CarMaxBoostTime). If the player boosts for too long the drag is doubled for a time
// (CarBoostMaxCooldownTime)
void CHoverCar_Player::ProcessBoost(const bool& BoostKeyPress, const float& DeltaTime)
{
	// process states
	if (BoostKeyPress)
	{
		if (CanBoost && !IsBoostCooldown)
		{
			IsBoosting = true;
		}
		else
		{
			IsBoosting = false;
		}
	}
	else
	{
		IsBoosting = false;
		BoostMultiplier = 1.0f;
	}

	// process boost timers
	if (IsBoosting)
	{
		BoostTimer += DeltaTime;
		BoostMultiplier = CarBoostMaxMultiplier;

		// check if boost timer exceeds max - if it does then set mIsBoostCooldown true & set mBoostCooldownTimer to max
		if (BoostTimer >= CarMaxBoostTime)
		{
			IsBoostCooldown = true;
			BoostCooldownTimer = CarBoostMaxCooldownTime;
			BoostTimer = 0.0f;
			DragMultiplier = CarDragMaxMultiplier;
			BoostMultiplier = 1.0f;
		}
	}
	else if (IsBoostCooldown)
	{
		BoostCooldownTimer -= DeltaTime;
		// check for the cooldown running out of time!
		if (BoostCooldownTimer <= 0)
		{
			IsBoostCooldown = false;
			DragMultiplier = 1.0f;
		}
	}
	else // !mIsBoosting && !mIsBoostCooldown
	{
		if (BoostTimer > 0.0f)
		{
			BoostTimer -= DeltaTime;
		}
	}
}

// The car bobs up and down slowly
void CHoverCar_Player::Bobble(const float& DeltaTime)
{
	if (IsMovingUp)
	{
		CarModel->MoveY(CarBobbleSpeed * DeltaTime);

		if (CarModel->GetY() >= CarBobbleMaxY)
		{
			IsMovingUp = false;
		}
	}
	else // !mIsMovingUp
	{
		CarModel->MoveY(-CarBobbleSpeed * DeltaTime);

		if (CarModel->GetY() <= CarBobbleMinY)
		{
			IsMovingUp = true;
		}
	}
}

// The car rotates left/right when the player presses the left/right keys
void CHoverCar_Player::ProcessRotation(const bool& LeftKeyPress, const bool& RightKeyPress, const float& DeltaTime)
{
	if (LeftKeyPress)
	{
		CarDummy->RotateY(-CarDefaultRotationSpeed * DeltaTime);
	}

	if (RightKeyPress)
	{
		CarDummy->RotateY(CarDefaultRotationSpeed * DeltaTime);
	}
}

// The car tilts slowly left/right when the player steers left/right
void CHoverCar_Player::Tilt(const float& DeltaTime, const bool& RightKeyPress, const bool& LeftKeyPress)
{
	// Steering right tilt
	if (RightKeyPress && TiltAngle >= -CarTiltLimit)
	{
		CarModel->RotateZ(-CarTiltSpeed * DeltaTime);
		TiltAngle -= CarTiltSpeed * DeltaTime;
	}
	else if (TiltAngle <= 0.0f)
	{
		CarModel->RotateZ(CarTiltReturnSpeed * DeltaTime);
		TiltAngle += CarTiltReturnSpeed * DeltaTime;
	}

	// Steering left tilt
	if (LeftKeyPress && TiltAngle <= CarTiltLimit)
	{
		CarModel->RotateZ(CarTiltSpeed * DeltaTime);
		TiltAngle += CarTiltSpeed * DeltaTime;
	}
	else if (TiltAngle >= 0.0f)
	{
		CarModel->RotateZ(-CarTiltReturnSpeed * DeltaTime);
		TiltAngle -= CarTiltReturnSpeed * DeltaTime;
	}
}

// The car leans up slightly at the front when accelerating, and back slightly when decelerating
void CHoverCar_Player::Lift(const float& DeltaTime, const float& ThrustFactor)
{
	if (ThrustFactor > 0.0f)
	{
		if (LiftAngle <= CarLiftUpperLimit)
		{
			CarModel->RotateX(CarLiftSpeed * DeltaTime);
			LiftAngle += CarLiftSpeed * DeltaTime;
		}
	}
	else if (ThrustFactor < 0.0f)
	{
		if (LiftAngle >= CarLiftLowerLimit)
		{
			CarModel->RotateX(-CarLiftSpeed * DeltaTime);
			LiftAngle -= CarLiftSpeed * DeltaTime;
		}
	}
	else // thrustFactor == 0.0f
	{
		if (LiftAngle >= 0.0f)
		{
			CarModel->RotateX(-CarLiftReturnSpeed * DeltaTime);
			LiftAngle -= CarLiftReturnSpeed * DeltaTime;
		}
		else if (LiftAngle <= 0.0f)
		{
			CarModel->RotateX(CarLiftReturnSpeed * DeltaTime);
			LiftAngle += CarLiftReturnSpeed * DeltaTime;
		}
	}
}

// Reduces player health by 1. Calls CheckHealth()
void CHoverCar_Player::TakeDamage()
{
	Health--;

	CheckHealth();
}

// Checks player health to see if player is alive and if they can boost
void CHoverCar_Player::CheckHealth()
{
	if (Health < 0)
	{
		IsAlive = false;
	}
	else if (Health < CarMinHealthForBoost)
	{
		CanBoost = false;
	}
}

// Check for collisions with <counter> checkpoint (point to box)
void CHoverCar_Player::CheckpointCollision(std::vector<CCheckpoint_LI>& CheckpointsVec, const float& NumLaps)
{
	if (SphereCollider.SphereToBox(CheckpointsVec.at(CheckpointCounter).GetTriggerZone()))
	{
		// Make cross appear
		CheckpointsVec.at(CheckpointCounter).MakeCrossAppear();

		// Increase checkpoint counter
		CheckpointCounter++;

		// If completed a lap, reset checkpoint counter to 0 and increase lap counter.
		if (CheckpointCounter == CheckpointsVec.size())
		{
			LapCounter++;
			CheckpointCounter = 0;

			// Check for finishing the race
			if (LapCounter == NumLaps)
			{
				// RACE OVER - ADD LATER
			}
		}
	}
}
//void CPlayerCar::CheckpointCollision(std::vector <SCheckpoint>& cpVec, const float& numLaps, EGameState& gameState)
//{
//	if (PointToBoxXZ(mDummyModel, cpVec.at(mCheckpointCounter).model, cpVec.at(mCheckpointCounter).width, cpVec.at(mCheckpointCounter).depth))
//	{
//		// make cross appear
//		cpVec.at(mCheckpointCounter).cross.lifeTimer = kCrossLifeTimer;
//		cpVec.at(mCheckpointCounter).cross.model->SetY(kCrossVisibleHeight);
//		cpVec.at(mCheckpointCounter).cross.isVisible = true;
//
//		// increase checkpoint counter
//		mCheckpointCounter++;
//
//		// reset checkpoint counter to 0 when a lap completes and increase lap counter.
//		if (mCheckpointCounter == cpVec.size())
//		{
//			mLapCounter++;
//			mCheckpointCounter = 0;
//
//			// check for finishing the race
//			if (mLapCounter == numLaps)
//			{
//				gameState = gRaceOver;
//			}
//		}
//	}
//}