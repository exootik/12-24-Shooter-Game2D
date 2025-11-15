#pragma once
#include "Obstacle.h"

class ObstacleDestructible : public Obstacle
{
public:
	ObstacleDestructible(float width, float height, int layer, const Color& color, Scene* pScene);
	ObstacleDestructible(float width, float height, int layer, Scene* pScene);

	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
};

