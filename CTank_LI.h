#pragma once

#include "CLevelItem.h"

#include <TL-Engine11.h>
#include "CCollider_Sphere.h"

using namespace tle;

// Tank constants
const float TankSinkHeight = -8.0f;
const float TankRadius = 3.0f;

class CTank_LI :
    public CLevelItem
{
private:
    Model* TankModel;
    CCollider_Sphere SphereCollider;
    
public:
    // constructors
    CTank_LI();
    CTank_LI(IMesh* TankMesh);
    CTank_LI(IMesh* TankMesh, const Vector2D& Position, const float& XRotation);

    // destructors
    ~CTank_LI();

    // setters

    // getters
};

