#pragma once

#include "Entity.h"

class Projectile : public Entity
{
public:
    Projectile(float width, float height, int layer, const Color& color,bool hasCollision, Scene* pScene);
    Projectile(float width, float height, int layer, Scene* pScene);

    void OnUpdate() override;
    void OnCollision(Entity* collidedWith) override;

    void ShootProjectile1(Entity* player);
    void ShootProjectile2(Entity* player);

    void DestroyProjectile3();

	void ShootProjectileEnemy1(Entity* enemy);
	void ShootProjectileEnemy3Laser(Entity* enemy);
	void ShootProjectileBossLaser(Entity* enemy);

	Projectile* pProjectile2;
	Projectile* pProjectileUltimate;

	bool proj2 = false;
	bool proj2HaveTarget = false;
	bool proj3 = false;
	bool projUltimate = false;
	bool projEnemy = false;
	bool projEnemyLaser = false;
	bool projBossLaser = false;

	float m_tempTime = 0.0f;
	float m_destroyProjectileTimer = 2.0f;
	float m_positionInitialX;
	float m_positionInitialY;
	float positionEnemyX;
	float positionEnemyY;
	float m_colisionSize = 3000;
};