#include "pch.h"
#include "Color.h"
#include "DirectXMath.h"

Color::Color(UI8 r, UI8 g, UI8 b, UI8 a) : m_r(r), m_g(g), m_b(b), m_a(a)
{}

sf::Color Color::ToSFMLColor()
{
	sf::Color color(m_r, m_g, m_b, m_a);
	return color;
}
DirectX::XMFLOAT4& Color::ToDirectXColor()
{
	DirectX::XMFLOAT4 color(m_r, m_g, m_b, m_a);
	return color;
}
;

const Color Color::Black = Color(0, 0, 0, 255);
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::Yellow = Color(255, 222, 33, 255);
const Color Color::Pink = Color(255, 192, 203, 255);
const Color Color::Purple = Color(128, 0, 128, 255);
const Color Color::Brown = Color(165, 42, 42, 255);
const Color Color::Grey = Color(128, 128, 128, 255);