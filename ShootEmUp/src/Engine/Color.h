#pragma once
#include "pch.h"

namespace sf {
	class Color;
}

class Color
{
public:
	Color(): m_r(0), m_g(0), m_b(0), m_a(0) {}
	Color(UI8 r, UI8 g, UI8 b, UI8 a = 255);
	~Color() {};

	void SetColor(UI8 r, UI8 g, UI8 b, UI8 a) {
		m_r = r;
		m_g = g;
		m_b = b;
		m_a = a;
	}

	void SetAlpha(UI8 a) { m_a = a; }

	Color* GetColor() { return this; }

	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Pink;
	static const Color Purple;
	static const Color Brown;
	static const Color Grey;

	sf::Color ToSFMLColor();

	DirectX::XMFLOAT4& ToDirectXColor();

protected:
	UI8 m_r, m_g, m_b, m_a;
};

