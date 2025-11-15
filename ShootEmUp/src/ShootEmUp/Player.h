#pragma once

#include "Entity.h"
#include "AssetManager.h"

class Projectile;

class Player : public Entity
{
public:
	Player(float width, float height, int layer, const Color& color, bool hasCollision, Scene* pScene);
	Player(float width, float height, int layer, Scene* pScene);
	
	void OnUpdate() override;
	void OnCollision(Entity* collidedWith) override;

	void Movement(const GCInputSystem* inputsystem);
	void DoUltimate();
	void DoBoostSpeed();
	void UpdateSprite();

	int GetScore() { return m_scorePlayer; }
	void IncrementScore() { m_scorePlayer++; }
	void resetScore() { m_scorePlayer = 0; }

	Projectile* pProjectileUltimate;

	bool m_canMoveUp = true;
	bool m_canMoveDown = true;
	bool m_canMoveLeft = true;
	bool m_canMoveRight = true;

	float m_maxLifePoint = 200	;
	float m_lifePoint = m_maxLifePoint;
	int m_maxBulletOfProjectile2 = 6;
	int m_bulletOfProjectile2 = m_maxBulletOfProjectile2;

	float m_durationOfSpeedBoost = 5.0f;
	float m_durationOfUltimate = 8.0f;
	float m_tempTime = 0.0f;
	float m_tempTimeForBoostSpeed = 0.0f;
	float m_tempTimeForUltimate = 0.0f;

	Sprite* m_spriteNormal = AssetManager::GetSprite("Voiture1").resource;
	Sprite* m_sprite33 = AssetManager::GetSprite("Voiture2").resource;
	Sprite* m_sprite66 = AssetManager::GetSprite("Voiture3").resource;

private:
	float m_speed = 500.0f;
	int m_scorePlayer = 0;

	bool m_boostSpeed = false; 
	bool m_doUltimate = false;
	bool m_canDoFireOfUltimate = true;
};
