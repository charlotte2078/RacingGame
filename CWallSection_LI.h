#pragma once

#include <TL-Engine11.h>
#include "CLevelItem.h"
#include "CCollider_Box.h"

using namespace tle;

// Wall section constants
const float WallOffset = 8.0f;
const float IsleOffset = 16.0f;
const int NumIsles = 3;
const int NumWalls = 2;
const float WallColliderWidth = 5.0f;
const float WallColliderDepth = 38.3f;

class CWallSection_LI :
    public CLevelItem
{
private:
    Model* DummyModel;
    Model* IslesArr[NumIsles];
    Model* WallsArr[NumWalls];
    CCollider_Box BoxCollider;

public:
    // constructors
    CWallSection_LI();
    CWallSection_LI(Mesh* DummyMesh, Mesh* WallMesh, Mesh* IsleMesh, const CVector2D& Pos, const float& Rot);

    // destructor
    ~CWallSection_LI();

    // setters

    // getters
};

