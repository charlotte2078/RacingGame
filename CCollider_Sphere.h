#pragma once
#include "CCollider.h"
class CCollider_Sphere :
    public CCollider
{
private:
    float Radius;

public:
    // constructors

    // destructors

    // setters
    void SetRadius(const float&);

    // getters
    float GetRadius() const;
};

