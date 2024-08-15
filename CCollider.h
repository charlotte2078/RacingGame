#pragma once

#include <TL-Engine11.h>

using namespace tle;

class CCollider
{
protected:
	Model* ColliderCentre;

public:
	// Constructors
	CCollider();
	CCollider(Mesh* DummyMesh, Model* BaseObject);

	// Destructors
	~CCollider();

	// Setters

	// Getters
};

