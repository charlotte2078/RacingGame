#pragma once

class Vector2D
{
private:
	float X; // = 0.0f using defualt constructor
	float Y; // = 0.0f using default constructor

public:
	// Constructors
	Vector2D(); // Default constructor
	Vector2D(const float& NewX, const float& NewY);

	// Destructors
	~Vector2D(); // Default destructor

	// Getters
	float GetX() const { return X; }
	float GetY() const { return Y; }

	// Setters
	void SetX(const float NewX) { X = NewX; }
	void SetY(const float NewY) { Y = NewY; }

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
	Vector2D ReflectInVector(const Vector2D& OtherVec);
	float Distance(const Vector2D& OtherVec) const;
	float SquareDistance(const Vector2D& OtherVec) const;
};
