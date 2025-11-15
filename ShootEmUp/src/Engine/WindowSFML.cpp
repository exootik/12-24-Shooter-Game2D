#include "pch.h"
#include "WindowSFML.h"

#include "MyWindow.h"
#include "Entity.h"

#include "Debug.h"
#include "AssetManager.h"
#include "Sprite.h"
#include "SpriteSFML.h"

WindowSFML::WindowSFML(unsigned int width, unsigned int height, const char* title) 
	: MyWindow(width,height), m_pWindow(new sf::RenderWindow(sf::VideoMode(width, height), title))
{
	SetInitPos(m_pWindow->getPosition().x, m_pWindow->getPosition().y);
}

void WindowSFML::Update()
{
	sf::Event event;
	while (m_pWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_isOpen = false;
		}

	}
}

void WindowSFML::Close()
{
	m_pWindow->close();
}


void WindowSFML::Draw(std::vector<std::list<Entity*>> entities)
{
	m_pWindow->clear(m_backgroundColor.ToSFMLColor());

	for (int i = 0; i < entities.size(); i++)
		for (Entity* entity : entities[i])
		{
			if (entity->GetSprite() != nullptr)
				entity->GetSprite()->Draw(this);
			else if (entity->GetRect() != nullptr)
				Draw(entity->GetRect());
			else
				std::cout << "Entity " << entity->GetName() << " Don't Have Sprite or Shape" << std::endl;

			if (entity->m_isColliderDisplay)
				entity->DrawCollider(this);
			entity->OnDraw(this);
		}

	Debug::Get()->Draw(this);

	mCaow->GetSprite()->Draw(this);

	m_pWindow->display();
}

void WindowSFML::SetFramerateLimit(int fps)
{
	_ASSERT(m_pWindow != nullptr);
	m_pWindow->setFramerateLimit(fps);
}

Sprite* WindowSFML::CreateSprite(const char* texturename)
{
	Sprite* sprite = new SpriteSFML(); 
	sprite->SetTexture(texturename);
	return sprite;
}

Sprite* WindowSFML::CreateSpriteWithAtlas(const char* atlasName, const char* assetName)
{
	Sprite* sprite = new SpriteSFML();
	sprite->SetTexture(atlasName);
	sprite->ResizeTexture(AssetManager::Get()->GetAtlasAsset(atlasName, assetName).resource);
	return sprite;
}

void WindowSFML::Draw(TextShape* text)
{
	SFMLText sfTxt = *dynamic_cast<SFMLText*>(text);
	m_pWindow->draw(sfTxt.m_sfText);
}

void WindowSFML::Draw(CircleShape* circle)
{
	SFMLCircle sfCircle = *dynamic_cast<SFMLCircle*>(circle);
	m_pWindow->draw(sfCircle.m_sfCircle);
}

void WindowSFML::Draw(RectShape* rect)
{
	SFMLRectShape sfRect = *dynamic_cast<SFMLRectShape*>(rect);
	m_pWindow->draw(sfRect.m_sfRect);
}





