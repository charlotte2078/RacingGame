#include "CVector2D.h"
#include "math.h" // sqrt()

CVector2D::CVector2D() :
    // Defualt values of X = 0.0f, Y = 0.0f
    X(0.0f),
    Y(0.0f)
{
}

CVector2D::CVector2D(const float& NewX, const float& NewY) :
    X(NewX),
    Y(NewY)
{
}

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

CVector2D CVector2D::operator*(float const& K)
{
    CVector2D Res;
    Res.X = X * K;
    Res.Y = Y * K;
    
    return Res;
}

float CVector2D::DotProduct(const CVector2D& OtherVec) const
{   
    return (X * OtherVec.GetX() + Y * OtherVec.GetY()) ;
}

CVector2D CVector2D::Normalise() const
{
    float Length = Magnitude();

    CVector2D Res;
    Res.SetX(X / Length);
    Res.SetY(Y / Length);

    return Res;
}
