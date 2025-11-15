#pragma once

class Entity;
class Sprite;
#include "DrawableShapes.h"


class MyWindow
{
public:
	MyWindow(int width, int height);
	~MyWindow() {};

	virtual void SetFramerateLimit(int fps) = 0;
	bool IsOpen() { return m_isOpen; }

	virtual void Draw(std::vector<std::list<Entity*>> entities) = 0;

	Vect2 GetPos() { return m_pos; }
	void SetPos(int x, int y) { m_pos.SetVector(x, y); }
	void SetPos(Vect2 pos) { m_pos = pos; }
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }

	void SetBackGroundColor(Color& color) { m_backgroundColor = color; }

	virtual void Update() = 0;
	virtual void Close() = 0;

	virtual Sprite* CreateSprite(const char* texturename) = 0;
	virtual Sprite* CreateSpriteWithAtlas(const char* atlasName, const char* assetName) = 0;

	virtual RectShape* CreateRectShape(const Color& color) = 0;
	virtual CircleShape* CreateCircleShape(const Color& color) = 0;
	virtual TextShape* CreateText(const Color& color, const char* text) = 0;

	virtual void Draw(TextShape* pText) = 0;
	virtual void Draw(CircleShape* pCircle) = 0;
	virtual void Draw(RectShape* pRect) = 0;

protected:
	void SetInitPos(int x, int y) { m_pos.SetVector(x,y); }

protected:
	bool m_isOpen;

	Vect2 m_pos;
	int m_width, m_height;

	Color m_backgroundColor;

	Entity* mCaow;

	friend class Debug;
	friend class GameManager;
	friend class Scene;
};

