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
    CCollider_Box();
    CCollider_Box(const CVector2D&);
    CCollider_Box(const CVector2D&, const CVector2D&);

    // Destructor
    ~CCollider_Box();

    // Setters
    void SetWidthDepth(const CVector2D&);

    // Getters
    CVector2D GetWidthDepth() const;

    // 

};

