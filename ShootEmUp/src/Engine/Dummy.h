#pragma once
#include "Entity.h"

class Scene;

class DummyEntity : public Entity
{
	TextShape* m_pText;


public:
	DummyEntity(float width, float height, int layer, Scene* pScene)
		: Entity(width, height, layer, true, Color::Red, pScene)
	{
		m_tag = -1;
		//AddTagWithoutCollision(0);
		m_pText = m_pScene->GetWindow()->CreateText(Color::Green, "TAMERE");
		m_pText->SetSize(200);
	}

	DummyEntity(float width, float height, int layer, bool hasCollision, Scene* pScene)
		: Entity(width, height, layer, hasCollision, Color::Red, pScene)
	{
		m_pText = m_pScene->GetWindow()->CreateText(Color::Blue, "AAAA");
	}

	void OnDraw(MyWindow* pWindow);
	void OnUpdate();
	void OnCollision(Entity* other) override;
};