#pragma once

class CVector2D
{
public:
	float X;
	float Y;

public:
	float Magnitude() const;
	float SquareMagnitude() const;

	CVector2D operator+(CVector2D const& Vec);
	CVector2D operator-(CVector2D const& Vec);
};

