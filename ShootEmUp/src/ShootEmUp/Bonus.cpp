#include "Bonus.h"
#include "GameScene.h"
#include "Player.h"

Bonus::Bonus(float width, float height, int layer, const Color& color, Scene* pScene) : Entity(width, height, layer, true, color, pScene)
{

}

Bonus::Bonus(float width, float height, int layer, Scene* pScene) : Entity(width, height, layer, true, Color::Red, pScene) {}
void Bonus::OnUpdate()
{
	bool pGameReset = GetScene<GameScene>()->m_gameReset;
	if (pGameReset)
	{
		Destroy();
	}
}
void Bonus::OnCollision(Entity* collidedWith)
{

}
