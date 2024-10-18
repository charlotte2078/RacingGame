#pragma once

#include "Vector2D.h"
#include <TL-Engine11.h>

using namespace tle;

class CCollider
{
protected:
	Model* ColliderCentre;
	Vector2D CentrePosition;
	bool HasMoved;

	void UpdateCentrePosition();

public:
	// Constructors
	CCollider();
	CCollider(Mesh* DummyMesh);
	CCollider(Mesh* DummyMesh, Model* BaseObject);

	// Destructors
	~CCollider();

	// Setters
	void UpdateHasMoved();

	// Getters
	Vector2D GetPosition() const;

	// Other public functions
	void AttachToBase(Model* BaseModel);
};

