#pragma once

#include "CCollider.h"
#include "CVector2D.h"
#include "CCollider_Sphere.h"
#include "CCollider_Point.h"

const int NumBoxCorners = 4;

class CCollider_Box :
    public CCollider
{
private:
    CVector2D WidthDepth;
    CVector2D HalfWidthDepth;
    Model* CornersArray[NumBoxCorners]; // 0 = top left; 1 = top right; 2 = bottom left; 3 = bottom right

public:
    // Constructors
    CCollider_Box();
    CCollider_Box(const CVector2D& NewWidthDepth, Mesh* DummyMesh, Model* BaseObject);

    // Destructor
    ~CCollider_Box();

    // Setters
    void SetWidthDepth(const CVector2D&);

    // Getters
    CVector2D GetWidthDepth() const;
    CVector2D GetHalfWidthDepth() const;

    // Collision functions
    bool BoxToSphere(const CCollider_Sphere& Sphere);
    bool BoxToPoint(const CCollider_Point& Point);
};

