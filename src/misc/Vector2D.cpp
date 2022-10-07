#include "misc/Vector2D.h"

#include <math.h>

Vector2D::Vector2D(float x, float y)
	:m_x(x), m_y(y)
{
}


float Vector2D::length()
{
	return static_cast<float>(sqrt((m_x * m_x) + (m_y * m_y)));
}

Vector2D Vector2D::operator+(const Vector2D& v2) const
{
	return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D& Vector2D::operator*=(float scalar)
{
	m_x *= scalar;
	m_y *= scalar;

	return *this;
}

Vector2D Vector2D::operator*(float scalar)
{
	return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const
{
	return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

Vector2D& Vector2D::operator/=(float scalar)
{
	m_x /= scalar;
	m_y /= scalar;

	return *this;
}

Vector2D Vector2D::operator/(float scalar)
{
	return Vector2D(m_x / scalar, m_y / scalar);
}

void Vector2D::normalize()
{
	float L = length();
	if (L > 0) // Stops division by 0
	{
		(*this) *= 1 / L; // Normalizes this vector
	}
}
