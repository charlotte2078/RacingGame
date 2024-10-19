#pragma once

#include "CCollider.h"

// Forward declarations
class CCollider_Sphere;

const int NumBoxCorners = 4;
const int NumBoxAxes = 2;

class CCollider_Box :
    public CCollider
{
private:
    Vector2D WidthDepth;
    Vector2D HalfWidthDepth;
    Model* CornersArray[NumBoxCorners]; // 0 = top left; 1 = top right; 2 = bottom right; 3 = bottom left
    Vector2D CornersPositionArray[NumBoxCorners];
    Vector2D AxesArray[NumBoxAxes];

    void MoveCornerPositions();
    void UpdateCornersPosition();
    void UpdateAxesArray();
    bool CheckCollisionAxisBoxes(const Vector2D& Axis, CCollider_Box& OtherBox);
    void GetMinMaxVertexOnAxis(const Vector2D& Axis, float& Min, float& Max);

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
    bool BoxToSphere(const CCollider_Sphere& Sphere) const;
    bool SATBoxToSphere(const CCollider_Sphere& Sphere) const;
    bool SATBoxToBox(CCollider_Box& Box);

    // REMOVE LATER!!!!
    Model* GetCentre();

    // Make sphere collider a friend of box colliders
    friend class CCollider_Sphere;
};