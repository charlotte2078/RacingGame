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

CVector2D::~CVector2D()
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

CVector2D CVector2D::ReflectInVector(const CVector2D& OtherVec)
{
    CVector2D ThisVec(X, Y);
    CVector2D OtherVecNormalised = OtherVec.Normalise();
    const float CoefficientOfReflection = 2.0f * DotProduct(OtherVecNormalised);
    CVector2D Reflection = ThisVec - (OtherVecNormalised * CoefficientOfReflection);
    
    return Reflection;
}

CVector2D CVector2D::Normalise() const
{
    const float Length = Magnitude();

    CVector2D Res;
    Res.X = X / Length;
    Res.Y = Y / Length;

    return Res;
}
