#include "pch.h"
#include "Vect2.h"


Vect2::Vect2(float x, float y) :
    m_x(x),
    m_y(y)
{}

Vect2::~Vect2()
{}

Vect2 Vect2::Zero()
{
    return Vect2(0, 0);
}

void Vect2::SetVector(float x, float y)
{
    m_x = x;
    m_y = y;
}

void Vect2::Normalize()
{
    float invNorm = 1 / GetNorm();
    m_x *= invNorm;
    m_y *= invNorm;
}

float Vect2::GetNormSquared() const { return m_x * m_x + m_y * m_y; }

float Vect2::GetNorm() const { return sqrtf(GetNormSquared()); }

float Vect2::GetDistanceFrom(const Vect2* other)
{
    return sqrtf((other->m_x - m_x) * (other->m_x - m_x) + (other->m_y - m_y) * (other->m_y - m_y));
}

float Vect2::GetDistanceFrom(float x, float y)
{
    return sqrtf((x - m_x) * (x - m_x) + (y - m_y) * (y - m_y));
}

Vect2& Vect2::operator*=(const float& other)
{
    m_x *= other;
    m_y *= other;
    return *this;
}

Vect2 operator*(Vect2 left, const float& right)
{
    left *= right;
    return left;
}

Vect2& Vect2::operator+=(const Vect2& other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

Vect2 operator+(Vect2 left, const Vect2& right)
{
    left += right;
    return left;
}

Vect2& Vect2::operator-=(const Vect2& other)
{
    m_x -= other.m_x;
    m_y -= other.m_y;
    return *this;
}

Vect2 operator-(Vect2 left, const Vect2& right)
{
    left -= right;
    return left;
}

sf::Vector2f Vect2::ToSfmlVecf()
{
    return sf::Vector2f(m_x, m_y);
}

Vect2* Vect2::SFMLVecToVect2f(sf::Vector2f vec)
{
    return new Vect2(vec.x, vec.y);
}

Vect2 Vect2::SFMLVect2ToVect2(sf::Vector2f vect)
{
    return Vect2(vect.x,vect.y);
}

DirectX::XMFLOAT2 Vect2::ToXMFLOAT2()
{
    return DirectX::XMFLOAT2(m_x, m_y);
}


std::ostream& operator<<(std::ostream& os, const Vect2& vect)
{
	os << "x : " << vect.m_x << " y : " << vect.m_y << std::endl;
	return os;
}
