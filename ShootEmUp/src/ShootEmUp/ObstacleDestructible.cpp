#include "ObstacleDestructible.h"
#include "GameScene.h"
#include "Projectile.h"
#include "Player.h"

ObstacleDestructible::ObstacleDestructible(float width, float height, int layer, const Color& color, Scene* pScene) : Obstacle(width, height, layer, color, pScene)
{

}

ObstacleDestructible::ObstacleDestructible(float width, float height, int layer, Scene* pScene) : Obstacle(width, height, layer, pScene) {}

void ObstacleDestructible::OnUpdate()
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

void ObstacleDestructible::OnCollision(Entity* collidedWith)
{
	Projectile* p3 = GetScene<GameScene>()->pProjectile3;

	if (collidedWith->IsTag(GameScene::Tag::PROJECTILE))
	{
		if (!p3)
		{
			Destroy();
			collidedWith->Destroy();
		}
	}
}