#pragma once

#include <TL-Engine11.h>
#include "CVector2D.h"

using namespace tle;

const float CrossLifeTimer = 2.0f;
const float CrossVisibleHeight = 5.0f;
const float CrossHiddenHeight = -20.0f;
const float CrossScaleFactor = 0.5f;

class CCross
{
private:
	Model* CrossModel;
	float LifeTimer;
	bool bIsVisible;

public:
	// constructors
	CCross();
	CCross(IMesh* CrossMesh);

	// deconstructor
	~CCross();

	// setters
	void SetLifeTimer(const float&);
	void SetVisibility(const bool&);

	// getters
	float GetLifeTimer() const;
	bool GetVisibility() const;

	// 
};

