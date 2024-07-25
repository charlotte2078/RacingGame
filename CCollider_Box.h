#pragma once

#include "CCollider.h"
#include "CVector2D.h"

class CCollider_Box :
    public CCollider
{
private:
    CVector2D WidthDepth;

public:
    // Constructors

    // Destructor

    // Setters
    void SetWidthDepth(const CVector2D&);

    // Getters
    CVector2D GetWidthDepth() const;

    // 

};

