#include "CCross.h"

// Default constructor
CCross::CCross() :
	CrossModel(nullptr),
	LifeTimer(0.0f),
	bIsVisible(false)
{
}

// Destructor - does nothing
CCross::~CCross()
{
}

void CCross::CreateModel(Mesh* CrossMesh)
{
	CrossModel = CrossMesh->CreateModel();
}

void CCross::SetLifeTimer(const float& NewTimer)
{
	LifeTimer = NewTimer;
}

void CCross::SetVisibility(const bool& NewVisibility)
{
	bIsVisible = NewVisibility;
}

float CCross::GetLifeTimer() const
{
	return LifeTimer;
}

bool CCross::GetVisibility() const
{
	return bIsVisible;
}
