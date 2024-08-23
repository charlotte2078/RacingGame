#pragma once

#include "CCollider.h"
#include "CCollider_Box.h"
#include "CCollider_Sphere.h"

class CCollider_Point :
    public CCollider
{
public:
    // Constructors
    CCollider_Point();
    CCollider_Point(Mesh* DummyMesh, Model* BaseObject);

    // Destructors
    ~CCollider_Point();

    // Collision methods
    bool PointToBox(const CCollider_Box& Box);

};

