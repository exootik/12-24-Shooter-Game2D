#pragma once
#include "Entity.h"

class Caow : public Entity
{
	bool m_goback;
public:
	Caow(float width, float height, int layer, Scene* pScene)
		: Entity(width, height, layer, false, Color::Red, pScene)
	{
		m_tag = -1;
		SetPosition(2200, 700);
		SetScale(0.45f, 0.45f);
		m_name = "Caow";
	}

	void OnUpdate();
};

