#pragma once

class Vector2D
{
public:
	float X; // = 0.0f using defualt constructor
	float Y; // = 0.0f using default constructor

	// Constructors
	Vector2D(); // Default constructor
	Vector2D(const float& NewX, const float& NewY);

	// Destructors
	~Vector2D(); // Default destructor

	// Magnitude functions
	float Magnitude() const;
	float SquareMagnitude() const;
	Vector2D Normalise() const;

	// Operators for adding, subtracting, scalar multiplication
	void operator+=(const Vector2D& Vec);
	Vector2D operator+(const Vector2D& Vec) const;
	void operator-=(const Vector2D& Vec);
	Vector2D operator-(const Vector2D& Vec) const;
	void operator*=(const float& K);
	Vector2D operator*(const float& K) const;

	// Other functions interacting with other vectors
	float DotProduct(const Vector2D& OtherVec) const;
	Vector2D ReflectInVector(const Vector2D& OtherVec) const;
	float Distance(const Vector2D& OtherVec) const;
	float SquareDistance(const Vector2D& OtherVec) const;
	Vector2D PerpendicularVector() const;
};

