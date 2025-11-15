#include "pch.h"
#include "SpriteSFML.h"
#include "AssetManager.h"
#include "MyWindow.h"
#include "WindowSFML.h"
#include "Entity.h"

SpriteSFML::SpriteSFML()
{
	m_sprite = sf::Sprite();
}

SpriteSFML::~SpriteSFML()
{}

bool SpriteSFML::SetTexture(const char* textureName)
{
	SetTextureName(textureName);
	if (AssetManager::Get()->GetTexture(textureName).success)
	{
		m_sprite.setTexture(AssetManager::Get()->GetTexture(textureName).resource->m_sfmlTexture);
		m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
		m_textWidth = m_sprite.getTexture()->getSize().x;
		m_textHeight = m_sprite.getTexture()->getSize().y;
		m_spriteWidth = m_textWidth; m_spriteHeight = m_textHeight;
		m_sprite.setOrigin(m_textWidth/2, m_textHeight/2);

		return true;
	}
	std::cout << "Texture Not Loaded";
	return false;
}

void SpriteSFML::Draw(MyWindow* pWindow)
{
	WindowSFML* pWinSFML = dynamic_cast<WindowSFML*>(pWindow);
	pWinSFML->GetRenderWindow()->draw(m_sprite);
}

void SpriteSFML::Update(Entity* pEntity)
{
	m_sprite.setPosition(pEntity->GetPosition().ToSfmlVecf());
}

void SpriteSFML::SetScale(Vect2 scale)
{
	m_sprite.setScale(scale.ToSfmlVecf());
}

void SpriteSFML::ResizeTexture(Frames* pFrame)
{
	m_sprite.setTextureRect(sf::IntRect(pFrame->m_startX, pFrame->m_startY, pFrame->m_width, pFrame->m_height));
	m_sprite.setOrigin((pFrame->m_width) * 0.5, (pFrame->m_height) * 0.5);
	m_spriteWidth = pFrame->m_width;
	m_spriteHeight = pFrame->m_height;
}

Sprite* SpriteSFML::Duplicate()
{
	SpriteSFML* newSprite = new SpriteSFML();
	newSprite->SetTexture(m_textureName);
	newSprite->m_sprite.setTextureRect(m_sprite.getTextureRect());
	newSprite->m_spriteWidth = m_spriteWidth;
	newSprite->m_spriteHeight = m_spriteHeight;
	newSprite->m_sprite.setOrigin(m_sprite.getOrigin());
	return newSprite;
}
