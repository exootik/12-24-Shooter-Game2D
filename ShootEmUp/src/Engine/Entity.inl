#include "Entity.h"

#include "GameManager.h"

template<typename T>
T Entity::GetColliderShape()
{
	return dynamic_cast<T>(m_pColliderShape);
}

template<typename T>
T* Entity::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}


template<typename T>
T* Entity::CreateEntity(float width, float height, int layer, const Color& color)
{
	return GetScene()->CreateEntity<T>(width, height,color,layer);
}

template<typename T>
T* Entity::CreateEntity(float width, float height,Sprite* pSprite ,int layer)
{
	return GetScene()->CreateEntity<T>(width, height, pSprite ,layer);
}