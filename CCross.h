#pragma once

#include <TL-Engine11.h>
#include "CVector2D.h"

using namespace tle;

class CCross
{
private:
	Model* CrossModel;
	float LifeTimer;
	bool bIsVisible;

public:
	// constructors
	CCross();

	// deconstructor
	~CCross();

	// setters
	void CreateModel(Mesh*);
	void SetLifeTimer(const float&);
	void SetVisibility(const bool&);

	// getters
	float GetLifeTimer() const;
	bool GetVisibility() const;

	// 
};

