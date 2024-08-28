#pragma once

#include "CCollider.h"
#include "CCollider_Box.h"

class CCollider_Sphere :
    public CCollider
{
private:
    float Radius;

public:
    // constructors
    CCollider_Sphere();
    CCollider_Sphere(const float& NewRadius, Mesh* DummyMesh, Model* BaseObject);

    // destructors
    ~CCollider_Sphere();

    // setters
    void SetRadius(const float&);

    // getters
    float GetRadius() const;

    // collision functions
    bool SphereToSphere(const CCollider_Sphere& OtherSphere);
    bool SphereToBox(const class CCollider_Box& Box);
};

