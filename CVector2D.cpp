#include "CVector2D.h"
#include "math.h" // sqrt()


// Default constructor - creates a CVector2D with X = 0.0f and Y = 0.0f
CVector2D::CVector2D() :
    X(0.0f),
    Y(0.0f)
{
}

// Creates a CVector2D with X and Y passed in.
CVector2D::CVector2D(const float& NewX, const float& NewY) :
    X(NewX),
    Y(NewY)
{
}

// Destructor - does nothing
CVector2D::~CVector2D()
{
}

// Calculates the magnitude of a vector
float CVector2D::Magnitude() const
{
    return sqrt(X*X + Y*Y);
}

// Calculates the magnitude squared of a vector.
float CVector2D::SquareMagnitude() const
{
    return X*X + Y*Y;
}

// Vector addition
CVector2D CVector2D::operator+(CVector2D const& Vec) const
{
    return CVector2D(X + Vec.X, Y + Vec.Y);
}

// Vector subtraction
CVector2D CVector2D::operator-(CVector2D const& Vec) const
{
    return CVector2D(X - Vec.X, Y - Vec.Y);
}

// Scalar multiplication between a vector and a float.
CVector2D CVector2D::operator*(float const& K) const
{
    return CVector2D(X * K, Y * K);
}

// Calculates the dot product of two vectors.
float CVector2D::DotProduct(const CVector2D& OtherVec) const
{   
    return (X * OtherVec.GetX() + Y * OtherVec.GetY()) ;
}

// Reflects current vector in another vector. Returns the result.
CVector2D CVector2D::ReflectInVector(const CVector2D& OtherVec)
{
    const float CoefficientOfReflection = 2.0f * DotProduct(OtherVec.Normalise());
    CVector2D Reflection = *this - (OtherVec.Normalise() * CoefficientOfReflection);
    
    return Reflection;
}

// Returns the distance between current point and another point.
float CVector2D::Distance(const CVector2D& OtherVec) const
{
    return (*this - OtherVec).Magnitude();
}

// Returns the distance squared between current point and another point.
float CVector2D::SquareDistance(const CVector2D& OtherVec) const
{
    return (*this - OtherVec).SquareMagnitude();
}

// Returns normalised vector.
CVector2D CVector2D::Normalise() const
{
    const float Length = Magnitude();

    CVector2D Res;
    Res.X = X / Length;
    Res.Y = Y / Length;

    return Res;
}
