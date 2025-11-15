#pragma once
#include "Vect2.h"
#include "Color.h"

class WindowSFML;
class WindowRender;

class DrawableShape
{
protected:
	Vect2 m_pos;
	float m_width = 0.f, m_height = 0.f;
	Vect2 m_scale = Vect2(1.0f,1.0f);

	Color m_color;
public: 
	virtual void SetPosition(float x, float y) = 0;
	virtual void SetPosition(Vect2 pos) = 0;
	virtual void SetScale(float x, float y) = 0;

	Vect2& GetPos() { return m_pos; }
	Vect2& GetPos(float ratioX, float ratioY);
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }
	const Vect2& GetSize() { return Vect2(m_width, m_height); }
};

class TextShape : public DrawableShape
{
protected:
	const char* m_text;
	int m_size;

public: 
	virtual void SetText(const char* text) = 0;

	virtual void SetSize(int size) = 0;
};

class CircleShape: public DrawableShape
{
protected:
	float m_radius;

public: 
	virtual void SetRadius(float m_radius) = 0;

	float GetRadius() { return m_radius * m_scale.m_x; }
};

class RectShape : public DrawableShape
{
public: 
	virtual void SetSize(float width, float height) = 0;
	virtual void SetWidth(float width) = 0;
	virtual void SetHeight(float height) = 0;

	float GetWidth() { return m_width * m_scale.m_x; }
	float GetHeight() { return m_height * m_scale.m_y; }
};



class SFMLCircle : public CircleShape
{
	sf::CircleShape m_sfCircle;
public:
	SFMLCircle(const Color& color);
	~SFMLCircle();
	void SetRadius(float m_radius) override;

	void SetPosition(float x, float y) override;
	void SetPosition(Vect2 pos) override;
	void SetScale(float x, float y) override;

	friend WindowSFML;
};

class SFMLRectShape : public RectShape
{
	sf::RectangleShape m_sfRect;
public:
	SFMLRectShape(const Color& color);
	~SFMLRectShape();

	void SetSize(float width, float height) override;
	void SetWidth(float width) override;
	void SetHeight(float height) override;

	void SetPosition(float x, float y) override;
	void SetPosition(Vect2 pos) override;
	void SetScale(float x, float y) override;

	friend WindowSFML;
};

class SFMLText : public TextShape
{
	sf::Text m_sfText;
public:
	SFMLText(const Color& color, const char* text, const char* font = "Hack-Regular.ttf");
	~SFMLText();

	void SetText(const char* text) override;

	void SetPosition(float x, float y) override;
	void SetPosition(Vect2 pos) override;
	void SetScale(float x, float y) override;

	void SetSize(int size) override;

	friend WindowSFML;
};



class GCCircle : public CircleShape
{
	GCGeometry* m_pGeometry;
	GCMesh* m_pMesh;
	GCMaterial* m_pMaterial;

	DirectX::XMMATRIX m_worldMatrix;

	const char* textureCircle; // SpriteCircle (:

public:
	GCCircle(GCGraphics* pGraphics, const Color& color);
	~GCCircle();

	void SetRadius(float m_radius) override;

	void SetPosition(float x, float y) override;
	void SetPosition(Vect2 pos) override;
	void SetScale(float x, float y) override;

	void ComputeWorldMatrix();

	friend WindowRender;
};

class GCRect : public RectShape
{
	GCGeometry* m_pGeometry;
	GCMesh* m_pMesh;
	GCMaterial* m_pMaterial;

	DirectX::XMMATRIX m_worldMatrix;

public:
	GCRect(GCGraphics* pGraphics, const Color& color);
	~GCRect();

	void SetSize(float width, float height) override;
	void SetWidth(float width) override;
	void SetHeight(float height) override;

	void SetPosition(float x, float y) override;
	void SetPosition(Vect2 pos) override;
	void SetScale(float x, float y) override;

	void ComputeWorldMatrix();
	friend WindowRender;
};

class GCText : public TextShape
{
	GCGeometry* m_pGeometry;
	GCMesh* m_pMesh;
	GCMaterial* m_pMaterial;

	DirectX::XMMATRIX m_worldMatrix;

public:
	GCText(GCGraphics* pGraphics, const Color& color, const char* text);
	~GCText();

	void SetText(const char* text) override;

	void SetPosition(float x, float y) override;
	void SetPosition(Vect2 pos) override;
	void SetScale(float x, float y) override;

	void SetSize(int size) override;

	void ComputeWorldMatrix();
	friend WindowRender;
};