#include "ObstacleIndestructible.h"
#include "GameScene.h"
#include "player.h"

ObstacleIndestructible::ObstacleIndestructible(float width, float height, int layer, const Color& color, Scene* pScene) : Obstacle(width, height, layer, color, pScene)
{

}

ObstacleIndestructible::ObstacleIndestructible(float width, float height, int layer, Scene* pScene) : Obstacle(width, height, layer, pScene) {}


void ObstacleIndestructible::OnUpdate()
{
	bool pGameReset = GetScene<GameScene>()->m_gameReset;
	if (pGameReset)
	{
		Destroy();
	}
	if (GetPosition().m_x < -50)
	{
		Destroy();
	}
}

void ObstacleIndestructible::OnCollision(Entity* collidedWith)
{

}