#pragma once

class CVector2D
{
private:
	float X; // = 0.0f using defualt constructor
	float Y; // = 0.0f using default constructor

public:
	// Constructors
	CVector2D(); // Default constructor
	CVector2D(const float&, const float&);

	// Destructors
	~CVector2D(); // Default destructor

	// Getters
	float GetX() const { return X; }
	float GetY() const { return Y; }

	// Setters
	void SetX(const float NewX) { X = NewX; }
	void SetY(const float NewY) { Y = NewY; }

	// Magnitude functions
	float Magnitude() const;
	float SquareMagnitude() const;
	CVector2D Normalise() const;

	// Operators for adding, subtracting, scalar multiplication
	CVector2D operator+(CVector2D const& Vec) const;
	CVector2D operator-(CVector2D const& Vec) const;
	CVector2D operator*(float const& K) const;

	// Other functions interacting with other vectors
	float DotProduct(const CVector2D& OtherVec) const;
	CVector2D ReflectInVector(const CVector2D& OtherVec);
	float Distance(const CVector2D& OtherVec) const;
	float SquareDistance(const CVector2D& OtherVec) const;
};

