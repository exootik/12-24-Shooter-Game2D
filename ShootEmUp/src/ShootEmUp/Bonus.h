#pragma once
#include "Entity.h"

class Bonus : public Entity
{
public:
	Bonus(float width, float height, int layer, const Color& color, Scene* pScene);
	Bonus(float width, float height, int layer, Scene* pScene);

	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
};

