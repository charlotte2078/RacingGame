#pragma once

#include "CLevelItem.h"

#include <TL-Engine11.h>
#include "CCollider_Sphere.h"

using namespace tle;

class CTank_LI :
    public CLevelItem
{
private:
    Model* TankModel;
    CCollider_Sphere SphereCollider;
    
public:
    // constructors

    // destructors

    // setters

    // getters
};

