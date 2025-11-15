#pragma once

#include <list>
#include <vector>
#include "MyWindow.h"

class GameManager;
class GCInputSystem;
class Color;
class Sprite;
class Entity;
class Caow;

class Scene
{
private:
	GameManager* m_pGameManager;

	int m_maxLayer;

	bool m_getCaowed;

protected:
	std::list<Entity*> m_entitiesToDestroy;
	std::list<Entity*> m_entitiesToAdd;

	std::vector<std::list<Entity*>> m_entitiesSortByLayer;
	std::list<Entity*> m_allEntities;
	std::list<Entity*> m_collidingEntities;

private:
	void SetGameManager(GameManager* pGameManager) { m_pGameManager = pGameManager; }
	
	void Update();
	void FixedUpdate();
	void Draw(MyWindow* pWindow);

protected:
	Scene();
	virtual ~Scene();

	virtual void LoadAssets() = 0;
	virtual void OnInitialize() = 0;
	virtual void OnEvent(const GCInputSystem* inputsystem) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnFixedUpdate() = 0;

public:
	template<typename T>
	T* CreateEntity(float width, float height, Sprite* sprite, int layer = 0);

	template<typename T>
	T* CreateEntity(float width, float height, const Color& color, int layer = 0, bool hasCollision = true);

	void ChangeEntityLayer(Entity* pEntity, int newLayer);

	float GetDeltaTime() const;
	void SetMaxLayer(int maxLayer);

	int GetWindowWidth() const;
	int GetWindowHeight() const;
	MyWindow* GetWindow() const;

	Sprite* CreateSprite(const char* filename) { return GetWindow()->CreateSprite(filename); }
	Sprite* CreateSpriteWithAtlas(const char* atlasName, const char* assetName) { return GetWindow()->CreateSpriteWithAtlas(atlasName, assetName); }

	GameManager* GetGameManager() { return m_pGameManager; }
	friend GameManager;
	friend Caow;
};

#include "Scene.inl"