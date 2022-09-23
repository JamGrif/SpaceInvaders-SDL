#pragma once

#include <math.h>

class Vector2D
{
public:
	Vector2D(float x, float y)
		:m_x(x), m_y(y)
	{
	}

	float getX() { return m_x; }
	float getY() { return m_y; }

	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }

	// Pythagoras Theorem
	float length() { return sqrt((m_x * m_x) + (m_y * m_y)); }

	// Add together two vectors to return a new one
	Vector2D operator+ (const Vector2D& v2) const
	{
		return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
	}

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
	Vector2D operator* (float scalar)
	{
		return Vector2D(m_x * scalar, m_y * scalar);
	}

	Vector2D& operator*= (float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;

		return *this;
	}

	// Subtraction of two vectors
	Vector2D operator- (const Vector2D& v2) const
	{
		return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
	}

	friend Vector2D& operator-= (Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;

		return v1;
	}

	// Divide by a scaler number
	Vector2D operator/ (float scalar)
	{
		return Vector2D(m_x / scalar, m_y / scalar);
	}

	Vector2D& operator /= (float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;

		return *this;
	}

	// Normalize a vector
	void normalize()
	{
		float L = length();
		if (L > 0) // Stops division by 0
		{
			(*this) *= 1 / L; // Normalizes this vector
		}
	}

private:
	float m_x;
	float m_y;
};

