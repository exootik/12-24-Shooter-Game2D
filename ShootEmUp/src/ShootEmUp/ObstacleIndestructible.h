#pragma once
#include "Obstacle.h"

class ObstacleIndestructible : public Obstacle
{
public:
	ObstacleIndestructible(float width, float height, int layer, const Color& color, Scene* pScene);
	ObstacleIndestructible(float width, float height, int layer, Scene* pScene);

	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
};

