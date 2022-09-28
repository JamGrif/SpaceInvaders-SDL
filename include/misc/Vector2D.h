#pragma once

class Vector2D
{
public:
	Vector2D(float x, float y);

	float getX();
	float getY();

	void setX(float x);
	void setY(float y);

	// Pythagoras Theorem
	float length();

	// Add together two vectors to return a new one
	Vector2D operator+ (const Vector2D& v2) const;

	// Using friend means you can access .m_x and .m_y for both objects directly
	friend Vector2D& operator+= (Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;

		return v1;
	}

	/*
		With these two functions you can add two vectors together using standard addition operators:
		Vector2D v1(10, 11);
		Vector2D v2(35, 25);
		v1 += v2;
		Vector2D v3 = v1 + v2;
	*/

	// Multiply vector by a scalar number
	Vector2D operator* (float scalar);

	Vector2D& operator*= (float scalar);

	// Subtraction of two vectors
	Vector2D operator- (const Vector2D& v2) const;

	friend Vector2D& operator-= (Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;

		return v1;
	}

	// Divide by a scaler number
	Vector2D operator/ (float scalar);

	Vector2D& operator /= (float scalar);

	// Normalize a vector
	void normalize();

private:
	float m_x;
	float m_y;
};

