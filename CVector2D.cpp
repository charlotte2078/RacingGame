#include "CVector2D.h"
#include "math.h" // sqrt()

float CVector2D::Magnitude() const
{
    return sqrt(X*X + Y*Y);
}

float CVector2D::SquareMagnitude() const
{
    return X*X + Y*Y;
}

CVector2D CVector2D::operator+(CVector2D const& Vec)
{
    CVector2D Res;
    Res.X = X + Vec.X;
    Res.Y = Y + Vec.Y;
    
    return Res;
}

CVector2D CVector2D::operator-(CVector2D const& Vec)
{
    CVector2D Res;
    Res.X = X - Vec.X;
    Res.Y = Y - Vec.Y;

    return Res;
}
