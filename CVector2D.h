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

	// Getters
	float GetX() const { return X; }
	float GetY() const { return Y; }

	// Setters
	void SetX(const float NewX) { X = NewX; }
	void SetY(const float NewY) { Y = NewY; }

	// Magnitude functions
	float Magnitude() const;
	float SquareMagnitude() const;

	// Operators for adding, subtracting, scalar multiplication
	CVector2D operator+(CVector2D const& Vec);
	CVector2D operator-(CVector2D const& Vec);
	CVector2D operator*(float const& K);

	// Dot product function
	float DotProduct(const CVector2D&) const;
	CVector2D Normalise() const;
};

