#include "pch.h"
#include "Scene.h"

#include "GameManager.h"
#include "MyWindow.h"
#include "Caow.h"
#include "InputManager.h"
#include "AssetManager.h"

Scene::Scene() : m_entitiesSortByLayer(std::vector<std::list<Entity*>>(7)), m_maxLayer(7), m_pGameManager(nullptr)
{
	AssetManager::LoadTexture("CAOW");
	Sprite* sprite = GameManager::Get()->GetWindow()->CreateSprite("CAOW");
	m_pGameManager = GameManager::Get();
	m_pGameManager->GetWindow()->mCaow = CreateEntity<Caow>(10, 10, sprite);
}

int Scene::GetWindowWidth() const
{
	return m_pGameManager->GetWindow()->GetWidth();
}

int Scene::GetWindowHeight() const
{
	return m_pGameManager->GetWindow()->GetHeight();
}

MyWindow* Scene::GetWindow() const
{
	return m_pGameManager->GetWindow();
}

float Scene::GetDeltaTime() const
{
	return m_pGameManager->mDeltaTime;
}

void Scene::SetMaxLayer(int maxLayer)
{
	m_maxLayer = maxLayer;

	if (m_entitiesSortByLayer.size() != maxLayer)
		m_entitiesSortByLayer.resize(maxLayer);
}

void Scene::Update()
{
	OnUpdate();
	//Update
	for (auto it = m_allEntities.begin(); it != m_allEntities.end(); )
	{
		Entity* entity = *it;

		entity->Update();

		if (entity->ToDestroy() == false)
		{
			++it;
			continue;
		}

		m_entitiesToDestroy.push_back(entity);
		it = m_allEntities.erase(it);

	}


	for (auto it = m_entitiesToDestroy.begin(); it != m_entitiesToDestroy.end(); ++it)
	{
		Entity* EntityToDelete = *it;

		std::list<Entity*>::iterator colliderIT = std::find(m_collidingEntities.begin(), m_collidingEntities.end(), EntityToDelete);
		if (colliderIT != m_collidingEntities.end())
			m_collidingEntities.erase(colliderIT);

		std::list<Entity*>::iterator layerIT = std::find(m_entitiesSortByLayer[EntityToDelete->GetLayer()].begin(), m_entitiesSortByLayer[EntityToDelete->GetLayer()].end(), EntityToDelete);
		if (layerIT != m_entitiesSortByLayer[EntityToDelete->GetLayer()].end())
			m_entitiesSortByLayer[EntityToDelete->GetLayer()].erase(layerIT);

		delete* it;
	}

	m_entitiesToDestroy.clear();

	for (std::list<Entity*>::iterator it = m_entitiesToAdd.begin(); it != m_entitiesToAdd.end(); ++it)
	{
		Entity* pEntity = *it;
		m_allEntities.push_back(*it);
		m_entitiesSortByLayer[pEntity->GetLayer()].push_back(*it);
		if (pEntity->HasCollision())
			m_collidingEntities.push_back(*it);
	}

	m_entitiesToAdd.clear();
}

void Scene::FixedUpdate()
{
	OnFixedUpdate();

	for (auto it = m_allEntities.begin(); it != m_allEntities.end(); it++ )
	{
		Entity* entity = *it;

		entity->FixedUpdate();
	}

	//Collision
	for (auto it1 = m_collidingEntities.begin(); it1 != m_collidingEntities.end(); ++it1)
	{
		auto it2 = it1;
		++it2;
		for (; it2 != m_collidingEntities.end(); ++it2)
		{
			Entity* entity = *it1;
			Entity* otherEntity = *it2;

			if (entity->AllowedCollision(otherEntity) == false)
				continue;

			if (entity->IsColliding(otherEntity) == false)
				continue;
			
			entity->OnCollision(otherEntity);
			otherEntity->OnCollision(entity);
		}
	}
}

void Scene::Draw(MyWindow* pWindow)
{
	pWindow->Draw(m_entitiesSortByLayer);
}


Scene::~Scene()
{
	for (auto it : m_allEntities)
		delete it;
	m_allEntities.clear();

	for (int i = 0; i < m_entitiesSortByLayer.size(); i++)
		m_entitiesSortByLayer[i].clear();

	m_collidingEntities.clear();
}


void Scene::ChangeEntityLayer(Entity* pEntity, int newLayer)
{
	if (newLayer >= m_maxLayer) {
		std::cout << "Max Layer is" << m_maxLayer << std::endl;
		return;
	}

	if (newLayer >= m_entitiesSortByLayer.size())
		m_entitiesSortByLayer.resize(m_maxLayer);

	m_entitiesSortByLayer[pEntity->GetLayer()].remove(pEntity);
	m_entitiesSortByLayer[newLayer].push_back(pEntity);
}