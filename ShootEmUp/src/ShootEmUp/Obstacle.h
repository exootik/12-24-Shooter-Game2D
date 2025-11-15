#pragma once
#include "Entity.h"

class Obstacle : public Entity
{
protected:
	Obstacle(float width, float height, int layer, const Color& color, Scene* pScene) : Entity(width, height, layer, true, color, pScene) {}
	Obstacle(float width, float height, int layer, Scene* pScene) : Entity(width, height, layer, true, Color::Red, pScene) {}
};

