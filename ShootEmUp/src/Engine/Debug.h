#pragma once

#include <vector>
#include <string>

class GameManager;
class MyWindow;
class WindowSFML;
class WindowRender;

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>

struct TextShape;
struct CircleShape;
struct RectShape;

class Color;

class Debug
{
	std::vector<TextShape*> m_texts;
	std::vector<CircleShape*> m_circles;
	std::vector<RectShape*> m_rects;

	void Draw(MyWindow* pWindow);

public:
	static Debug* Get();

	static void CreateRectangle(float x, float y, float width, float height, const Color& color);
	static void CreateSquare(float x, float y, float width, const Color& color);
	static void CreateCircle(float x, float y, float radius, const Color& color);
	static void CreateText(float x, float y, const char* text, const Color& color, const char* fontName = "Hack-Regular.ttf");
	static void CreateText(float x, float y, const char* text, float ratioX, float ratioY, const Color& color, const char* fontName = "Hack-Regular.ttf");

	friend GameManager;
	friend MyWindow;
	friend WindowSFML;
	friend WindowRender;
};

