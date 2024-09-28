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

