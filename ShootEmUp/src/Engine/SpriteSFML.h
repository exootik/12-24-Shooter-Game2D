#pragma once
#include "Sprite.h"

class Entity;

class SpriteSFML : public Sprite
{
public:
	SpriteSFML();
	~SpriteSFML();
	bool SetTexture(const char* textureName);
	void Draw(MyWindow* pWindow); 
	void Update(Entity* pEntity);
	void SetScale(Vect2 scale);

	void ResizeTexture(Frames* pFrame) override;

protected: 
	Sprite* Duplicate() override;

protected: 
	sf::Sprite m_sprite;

};

