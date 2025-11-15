#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include "MyWindow.h"
#include <list>



namespace sf
{
	class RenderWindow;
	class Event;
}

class WindowSFML : public MyWindow
{
public: 
	WindowSFML(unsigned int width, unsigned int height, const char* title);
	~WindowSFML() {};


	void Draw(std::vector<std::list<Entity*>> entities) override;
	void SetFramerateLimit(int fps);

	void Update();
	void Close();

	sf::RenderWindow* GetRenderWindow() { return m_pWindow; }

	Sprite* CreateSprite(const char* texturename);
	Sprite* CreateSpriteWithAtlas(const char* atlasName, const char* assetName);

	RectShape* CreateRectShape(const Color& color) { return new SFMLRectShape(color); }
	CircleShape* CreateCircleShape(const Color& color) { return new SFMLCircle(color); }
	TextShape* CreateText(const Color& color, const char* text) { return new SFMLText(color,text); }

protected:
	void Draw(TextShape* pText);
	void Draw(CircleShape* pCircle);
	void Draw(RectShape* pRect);

protected:
	sf::RenderWindow* m_pWindow;

	friend Debug;

};

