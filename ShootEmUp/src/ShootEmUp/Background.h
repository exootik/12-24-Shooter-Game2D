#pragma once
#include "Entity.h"

class Background1 : public Entity
{
public:
	Background1(float width, float height, int layer, Color color, Scene* pScene) : Entity(width, height, layer, false, color, pScene){}
	Background1(float width, float height, int layer, Scene* pScene);

	void OnUpdate() override;

	bool m_canBeDuplicated = true;
};

class Background2 : public Entity
{
public:
	Background2(float width, float height, int layer, Color color, Scene* pScene) : Entity(width, height, layer, false, color, pScene) {}
	Background2(float width, float height, int layer, Scene* pScene);

	void OnUpdate() override;

	bool m_canBeDuplicated = true;
};

class Background3 : public Entity
{
public:
	Background3(float width, float height, int layer, Color color, Scene* pScene) : Entity(width, height, layer, false, color, pScene) {}
	Background3(float width, float height, int layer, Scene* pScene);

	void OnUpdate() override;

	bool m_canBeDuplicated = true;
};

class Background4 : public Entity
{
public:
	Background4(float width, float height, int layer, Color color, Scene* pScene) : Entity(width, height, layer, false, color, pScene) {}
	Background4(float width, float height, int layer, Scene* pScene);

	void OnUpdate() override;

	bool m_canBeDuplicated = true;
};