#pragma once

#include "pch.h"
#include "DirectXMath.h"

class Vect2 {
public:

    float m_x;
    float m_y;

    Vect2(): m_x(0.f), m_y(0.f) {}
    Vect2(float x, float y);
    ~Vect2();

    static Vect2 Zero();

    void SetVector(float x, float y);
    float GetX() { return m_x; }
    float GetY() { return m_y; }
    void SetX(float x) { x = x; }
    void SetY(float y) { y = y; }

    void Normalize();
    float GetNorm() const;
    float GetNormSquared() const;
    float GetDistanceFrom(const Vect2* other);
    float GetDistanceFrom(float x, float y);

    Vect2& operator*=(const float& other);
    friend Vect2 operator*(Vect2 left, const float& right);

    Vect2& operator+=(const Vect2& other);
    friend Vect2 operator+(Vect2 left, const Vect2& right);

    Vect2& operator-=(const Vect2& other);
    friend Vect2 operator-(Vect2 left, const Vect2& right);

    friend std::ostream& operator<<(std::ostream& os, const Vect2& integer);

    sf::Vector2f ToSfmlVecf();

    Vect2* SFMLVecToVect2f(sf::Vector2f vec);

    static Vect2 SFMLVect2ToVect2(sf::Vector2f vect);

    DirectX::XMFLOAT2 ToXMFLOAT2();
};

std::ostream& operator<<(std::ostream& os, const Vect2& integer);