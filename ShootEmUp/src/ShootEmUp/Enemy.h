#pragma once

#include "Entity.h"

class Projectile;
class Player;

class Enemy : public Entity
{
public:
	Enemy(float width, float height, int layer, const Color& color, bool hasCollision, Scene* pScene);
	Enemy(float width, float height, int layer, Scene* pScene);

	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;
	void Shoot();

	void SetTypeOfEnemy(int type) { m_typeOfEnemy = type; }
	int GetTypeOfEnemy() { return m_typeOfEnemy; }
	void SetDirectionX(float direction) { m_directionX = direction; }
	void SetDirectionY(float direction) { m_directionY = direction; }
	void SetLifePoint(int lifePoint) { m_lifePoint = lifePoint; }
	int GetLifePoint() { return m_lifePoint; }

	Enemy* pEnemy41;
	Projectile* pProjectileEnemy;
	Projectile* pProjectileEnemy2;

	float m_tempTime = 0.0f;
	float m_cooldownForShootEnemy = 1.0f;
	float m_cooldownForShootEnemy3 = 3.0f;
	float m_canShootTimerEnemy1 = 0.0f;
	float m_canShootTimerEnemy3 = 0.0f;
	float m_canShootTimerBoss = 0.0f;

	bool m_canShoot = true;
	bool m_canBossShoot = true;

private:
	int m_typeOfEnemy;
	float m_directionX = -1;
	float m_directionY = 0.3f;
	bool m_canChangeDirection = false;
	int m_lifePoint = 1;
};
