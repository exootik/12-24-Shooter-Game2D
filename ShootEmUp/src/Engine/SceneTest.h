#pragma once

#include "Scene.h"

class DummyEntity;
class GCInputSystem;

class SampleScene : public Scene
{
	DummyEntity* pEntity1;
	DummyEntity* pEntity2;

	Entity* pEntitySelected;

	float m_elapsed; 
	int m_eneCount;

private:
	void TrySetSelectedEntity(Entity* pEntity, int x, int y);

public:
	void LoadAssets() override {};
	void OnInitialize() override;
	void OnEvent(const GCInputSystem* inputSystem) override;
	void OnUpdate() override;
	void OnFixedUpdate() override {};
};