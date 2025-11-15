#include "pch.h"
#include "SceneTest.h"
#include "AssetManager.h"
#include "AnimationManager.h"
#include "MyWindow.h"

#include "Dummy.h"
#include "Color.h"
#include "Sprite.h"

#include "Debug.h"
#include "InputManager.h"

void SampleScene::OnInitialize()
{
	AssetManager::LoadSpriteSheet("Test", 68, 416, 256, 8, 13);
	
	AssetManager::LoadAtlas("Atlas");

	DummyEntity* dummy = CreateEntity<DummyEntity>(100, 100, AssetManager::GetSprite("Voiture1").resource, 1);

	Animation* pAnim = AnimationManager::CreateAnimation("oooo", "Test", 13, 8).resource;
	pAnim->SetSpeed(1.f);
	
	//Sprite* sprite2 = CreateSpriteWithAtlas("Atlas","BackGround");

	//dummy->PlayAnimation("oooo");
	dummy->SetPosition(500, 500);
	dummy->SetName("E1");
	//dummy->SetScale(10.f, 10.f);
	dummy->ShowCollision(false);
	dummy->SetCollisionSize(200,200);
	dummy->SetCollisionPosition(Vect2(0, 0));

	pEntity1 = dummy;

	m_eneCount = 1;


	m_elapsed = 50000000000000.f;

	//pEntity2 = CreateEntity<DummyEntity>(50, 50, sprite);
	//pEntity2->SetPosition(500, 500);
	//pEntity2->SetName("E2");
	//pEntity2->SetScale(0.45, 0.45);
	//pEntity2->ShowCollision(true);

	pEntitySelected = nullptr;
}

void SampleScene::OnEvent(const GCInputSystem* inputSystem)
{
	if (inputSystem->m_pMouse->GetKeyDown(GCMOUSE::RIGHT))
	{
		for (Entity* entity : m_collidingEntities)
		{
			TrySetSelectedEntity(entity, inputSystem->m_pMouse->GetMousePos().x, inputSystem->m_pMouse->GetMousePos().y);
		}
	}


	if (inputSystem->m_pMouse->GetKeyDown(GCMOUSE::LEFT))
	{
		if (pEntitySelected != nullptr)
		{
			pEntitySelected->GoToPosition(inputSystem->m_pMouse->GetMousePos().x, inputSystem->m_pMouse->GetMousePos().y, 100.f);
		}
	}
}

void SampleScene::TrySetSelectedEntity(Entity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntitySelected = pEntity;
}

void SampleScene::OnUpdate()
{
	if (pEntitySelected != nullptr)
	{
		Vect2 position = pEntitySelected->GetPosition();
		Debug::CreateCircle(position.m_x, position.m_y, 10, Color::Blue);
	}
	m_elapsed += GameManager::Get()->GetDeltaTime();
	if (m_elapsed >= 200000000.f) {
		m_elapsed = 0.f;
		DummyEntity* dummy = CreateEntity<DummyEntity>(100, 100, pEntity1->GetSprite(), 1);
		dummy->PlayAnimation("oooo");
		dummy->SetPosition(100, 10);
		dummy->SetName("AAA");
		dummy->SetScale(10.f, 10.f);
		dummy->SetCollisionSize(5,10);
		dummy->ShowCollision(true);

	}

}