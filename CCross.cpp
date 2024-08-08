#include "CCross.h"

// Default constructor
CCross::CCross() :
	CrossModel(nullptr),
	LifeTimer(0.0f),
	bIsVisible(false)
{
}

CCross::CCross(IMesh* CrossMesh) :
	LifeTimer(0.0f),
	bIsVisible(false)
{
	CrossModel = CrossMesh->CreateModel();
	CrossModel->Scale(CrossScaleFactor);
}

// Destructor - does nothing
CCross::~CCross()
{
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

// Attach the cross to the passed in model.
void CCross::AttachToCheckpoint(Model* ParentCP)
{
	CrossModel->AttachToParent(ParentCP);
}
