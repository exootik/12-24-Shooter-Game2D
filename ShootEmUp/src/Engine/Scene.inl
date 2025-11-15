#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "Entity.h"
#include "Color.h"
#include "Sprite.h"

template<typename T>
T* Scene::CreateEntity(float width, float height, Sprite* sprite, int layer)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T(width, height,layer, this);

	Entity* entity = newEntity;
	entity->SetSprite(sprite->Duplicate());

	m_entitiesToAdd.push_back(newEntity);

	return newEntity;
}

template<typename T>
T* Scene::CreateEntity(float width, float height, const Color& color, int layer, bool hasCollision)
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T(width, height, layer, color, hasCollision, this);

	m_entitiesToAdd.push_back(newEntity);

	return newEntity;
}