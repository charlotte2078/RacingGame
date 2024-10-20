#pragma once

#include "CCollider.h"

class CCollider_Box;

class CCollider_Sphere :
    public CCollider
{
private:
    float Radius;
    Vector2D Axis;

    // SAT collision functions
    void UpdateAxis(CCollider_Box& Box);
    void GetMinMaxVertexOnAxisSphere(const Vector2D& Axis, float& Min, float& Max);

public:
    // constructors
    CCollider_Sphere();
    CCollider_Sphere(const float& NewRadius, Mesh* DummyMesh, Model* BaseObject);

    // destructors
    ~CCollider_Sphere();

    // setters
    void SetRadius(const float& NewRadius);

    // getters
    float GetRadius() const;
    
    // REMOVE LATER
    Model* GetCentre();

    // collision functions
    bool SphereToSphere(const CCollider_Sphere& OtherSphere) const;

    friend class CCollider_Box;
};