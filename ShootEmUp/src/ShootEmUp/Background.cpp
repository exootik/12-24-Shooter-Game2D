#include "Background.h"
#include "GameManager.h"
#include "GameScene.h"*
#include "Color.h"
#include "AssetManager.h"

#include <iostream>


Background1::Background1(float width, float height, int layer,  Scene* pScene) : Entity(width, height, layer, false, Color::Black, pScene)
{
	SetPosition(GetWidth() / 2, GetHeight() / 2);
}

void Background1::OnUpdate()
{
	GameScene* bg = GetScene<GameScene>();

	SetDirection(-1.f, 0.f, 60.0f);

	if (GetPosition().m_x <= bg->GetWindowWidth() / 2 && m_canBeDuplicated)
	{
		m_canBeDuplicated = false;
		CreateEntity<Background1>(bg->GetWindowWidth(), bg->GetWindowHeight(), AssetManager::GetSprite("Town").resource, 0)->SetPosition(GetPositionWithCustomOrigin(1.f, 0.5f).m_x - 10, GetPositionWithCustomOrigin(1.f, 0.5f).m_y, 0.f, 0.5f);
	}
	if (GetPosition().m_x <= -1000)
	{
		Destroy();
	}
}

Background2::Background2(float width, float height, int layer, Scene* pScene) : Entity(width, height, layer, false, Color::Black, pScene)
{
	GameScene* bg = GetScene<GameScene>();

	SetPosition(GetWidth() / 2, GetHeight() / 2 );
}

void Background2::OnUpdate()
{
	GameScene* bg = GetScene<GameScene>();

	SetDirection(-1.f, 0.f, 120.f);

	if (GetPosition().m_x <= bg->GetWindowWidth() / 2 && m_canBeDuplicated)
	{
		m_canBeDuplicated = false;
		CreateEntity<Background2>(bg->GetWindowWidth(), (bg->GetWindowHeight() / 100) * 90, AssetManager::GetSprite("Clouds").resource,1)->SetPosition(GetPositionWithCustomOrigin(1.f, 0.5f).m_x - 10, GetPositionWithCustomOrigin(1.f, 0.5f).m_y, 0.f, 0.5f);
	}
	if (GetPosition().m_x <= -1000.0f)
	{
		Destroy();
	}
}

Background3::Background3(float width, float height, int layer, Scene* pScene) : Entity(width, height, layer, false, Color::Black, pScene)
{
	GameScene* bg = GetScene<GameScene>();

	SetPosition(GetWidth() / 2, GetHeight());
}
void Background3::OnUpdate()
{
	GameScene* bg = GetScene<GameScene>();

	SetDirection(-1.f, 0.f, 220.f);

	if (GetPosition().m_x <= bg->GetWindowWidth() / 2 && m_canBeDuplicated)
	{
		m_canBeDuplicated = false;
		CreateEntity<Background3>(bg->GetWindowWidth(), (bg->GetWindowHeight() / 100) * 80, AssetManager::GetSprite("Birds").resource, 2)->SetPosition(GetPositionWithCustomOrigin(1.f, 0.5f).m_x - 10, GetPositionWithCustomOrigin(1.f, 0.5f).m_y, 0.f, 0.5f);
	}
	if (GetPosition().m_x <= -1000)
	{
		Destroy();
	}
}

Background4::Background4(float width, float height, int layer, Scene* pScene) : Entity(width, height, layer, false, Color::Black, pScene)
{
	GameScene* bg = GetScene<GameScene>();

	SetPosition(GetWidth() / 2, GetHeight() * 0.665);
}

void Background4::OnUpdate()
{
	GameScene* bg = GetScene<GameScene>();

	SetDirection(-1.f, 0.f, 300.0f);

	if (GetPosition().m_x <= bg->GetWindowWidth() / 2 && m_canBeDuplicated)
	{
		m_canBeDuplicated = false;
		CreateEntity<Background4>(bg->GetWindowWidth(), (bg->GetWindowHeight() / 100) * 80, AssetManager::GetSprite("Road").resource, 3)->SetPosition(GetPositionWithCustomOrigin(1.f,0.5f).m_x - 10, GetPositionWithCustomOrigin(1.f, 0.5f).m_y,0.f,0.5f);
	}
	if (GetPosition().m_x <= -1000)
	{
		Destroy();
	}
}
