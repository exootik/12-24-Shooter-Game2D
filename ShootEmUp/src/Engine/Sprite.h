#pragma once

class MyWindow;
class Entity; 
class Scene;
class Frames;
class Animation;
class AssetManager;

class Sprite
{
public:
	Sprite(): m_textWidth(0.f), m_textHeight(0.f),m_textureName("") {};
	virtual ~Sprite() {};
	virtual bool SetTexture(const char* textureName) = 0;
	virtual void Draw(MyWindow* pWindow) = 0;
	virtual void Update(Entity* pEntity) = 0;
	virtual void SetScale(Vect2 scale) = 0;
	float GetTextureWidth() { return m_textWidth; }
	float GetTextureHeight() { return m_textHeight; }

	float GetSpriteWidth() { return m_spriteWidth; }
	float GetSpriteHeight() { return m_spriteHeight; }

	void SetSpriteWidthAndHeight(float width, float height) { m_spriteHeight = height; m_spriteWidth = width; }

	virtual void ResizeTexture(Frames* pFrame) = 0;

	virtual Sprite* Duplicate() = 0;
protected: 
	void SetTextureName(const char* textureName) { m_textureName = textureName; }

protected:
	const char* m_textureName;
	float m_textWidth, m_textHeight;
	float m_spriteWidth, m_spriteHeight;

	friend Scene;
	friend Animation;
	friend AssetManager;
};