#include "Vector2D.h"
#include "math.h" // sqrt()


// Default constructor - creates a CVector2D with X = 0.0f and Y = 0.0f
Vector2D::Vector2D() :
    X(0.0f),
    Y(0.0f)
{
}

// Creates a CVector2D with X and Y passed in.
Vector2D::Vector2D(const float& NewX, const float& NewY) :
    X(NewX),
    Y(NewY)
{
}

// Destructor - does nothing
Vector2D::~Vector2D()
{
}

// Calculates the magnitude of a vector
float Vector2D::Magnitude() const
{
    return sqrt(X*X + Y*Y);
}

// Calculates the magnitude squared of a vector.
float Vector2D::SquareMagnitude() const
{
    return X*X + Y*Y;
}

void Vector2D::operator+=(const Vector2D& Vec)
{
    X += Vec.X;
    Y += Vec.Y;
}

// Vector addition
Vector2D Vector2D::operator+(const Vector2D& Vec) const
{
    return Vector2D(X + Vec.X, Y + Vec.Y);
}

void Vector2D::operator-=(const Vector2D& Vec)
{
    X -= Vec.X;
    Y -= Vec.Y;
}

// Vector subtraction
Vector2D Vector2D::operator-(const Vector2D& Vec) const
{
    return Vector2D(X - Vec.X, Y - Vec.Y);
}

// Scalar multiplication between a vector and a float.
void Vector2D::operator*=(const float& K)
{
    X *= K;
    Y *= K;
}

// Scalar multiplication between a vector and a float.
Vector2D Vector2D::operator*(const float& K) const
{
    return Vector2D(X * K, Y * K);
}

// Calculates the dot product of two vectors.
float Vector2D::DotProduct(const Vector2D& OtherVec) const
{   
    return (X * OtherVec.X + Y * OtherVec.Y);
}

// Reflects current vector in another vector. Returns the result.
Vector2D Vector2D::ReflectInVector(const Vector2D& OtherVec)
{
    const float CoefficientOfReflection = 2.0f * DotProduct(OtherVec.Normalise());
    Vector2D Reflection = *this - (OtherVec.Normalise() * CoefficientOfReflection);
    
    return Reflection;
}

// Returns the distance between current point and another point.
float Vector2D::Distance(const Vector2D& OtherVec) const
{
    return (*this - OtherVec).Magnitude();
}

// Returns the distance squared between current point and another point.
float Vector2D::SquareDistance(const Vector2D& OtherVec) const
{
    return (*this - OtherVec).SquareMagnitude();
}

// Returns normalised vector.
Vector2D Vector2D::Normalise() const
{
    const float LengthFraction = 1.0f / Magnitude();

    return this->operator*(LengthFraction);
}
