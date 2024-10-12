#pragma once

#include "CCollider.h"
#include "CCollider_Box.h"
#include "CCollider_Point.h"

class CCollider_Sphere :
    public CCollider
{
private:
    float Radius;
    Vector2D Axis;

    void UpdateAxis(CCollider_Box& Box);

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
    bool SphereToSphere(const CCollider_Sphere& OtherSphere) const;
    bool SphereToBox(const class CCollider_Box& Box) const;
    bool SphereToPoint(const class CCollider_Point& Point) const;
};

