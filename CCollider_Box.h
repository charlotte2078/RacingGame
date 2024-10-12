#pragma once

#include "CCollider.h"
#include "Vector2D.h"
#include "CCollider_Sphere.h"
#include "CCollider_Point.h"

const int NumBoxCorners = 4;

class CCollider_Box :
    public CCollider
{
private:
    Vector2D WidthDepth;
    Vector2D HalfWidthDepth;
    Model* CornersArray[NumBoxCorners]; // 0 = top left; 1 = top right; 2 = bottom left; 3 = bottom right

    void MoveCornerPositions();

public:
    // Constructors
    CCollider_Box();
    CCollider_Box(const Vector2D& NewWidthDepth, Mesh* DummyMesh);
    CCollider_Box(const Vector2D& NewWidthDepth, Mesh* DummyMesh, Model* BaseObject);

    // Destructor
    ~CCollider_Box();

    // Setters
    void SetWidthDepth(const Vector2D& NewWD);

    // Getters
    Vector2D GetWidthDepth() const;
    Vector2D GetHalfWidthDepth() const;

    // Collision functions
    bool BoxToSphere(const class CCollider_Sphere& Sphere) const;
    bool BoxToPoint(const class CCollider_Point& Point) const;
};

