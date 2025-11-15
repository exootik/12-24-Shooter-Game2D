#include "pch.h"
#include "Debug.h"

#include "GameManager.h"
#include "AssetManager.h"

#include "MyWindow.h"

#include "DrawableShapes.h"
#include "Color.h"


Debug* Debug::Get()
{
	static Debug mInstance;

	return &mInstance;
}

void Debug::Draw(MyWindow* pWindow)
{

	for (TextShape* text : m_texts)
	{
		pWindow->Draw(text);
	}

	m_texts.clear();

	for (CircleShape* circle : m_circles)
	{
		pWindow->Draw(circle);
	}

	m_circles.clear();

	for (RectShape* rect : m_rects)
	{
		pWindow->Draw(rect);
	}

	m_rects.clear();
}


void Debug::CreateRectangle(float x, float y, float width, float height, const Color& color)
{
	RectShape* rect = GameManager::Get()->GetWindow()->CreateRectShape(color); 
	rect->SetWidth(width);
	rect->SetHeight(height);
	rect->SetPosition(Vect2(x, y));

	Debug::Get()->m_rects.push_back(rect);

}

void Debug::CreateSquare(float x, float y, float width, const Color& color)
{
	RectShape* rect = GameManager::Get()->GetWindow()->CreateRectShape(color);
	rect->SetWidth(width);
	rect->SetHeight(width);
	rect->SetPosition(Vect2(x, y));

	Debug::Get()->m_rects.push_back(rect);

}

void Debug::CreateCircle(float x, float y, float radius, const Color& color)
{
	CircleShape* circle = GameManager::Get()->GetWindow()->CreateCircleShape(color);
	circle->SetRadius(radius);
	circle->SetPosition(Vect2(x - radius, y - radius));

	Debug::Get()->m_circles.push_back(circle);
}

void Debug::CreateText(float x, float y, const char* text, const Color& color, const char* fontName)
{
	CreateText(x, y, text, 0.f, 0.f, color);
}

void Debug::CreateText(float x, float y, const const char* text, float ratioX, float ratioY, const Color& color, const char* fontName)
{
	_ASSERT(ratioX >= 0.f && ratioX <= 1.f);
	_ASSERT(ratioY >= 0.f && ratioY <= 1.f);

	TextShape* newText = GameManager::Get()->GetWindow()->CreateText(color, text);
	newText->SetPosition(x, y);

	Debug::Get()->m_texts.push_back(newText);
}
