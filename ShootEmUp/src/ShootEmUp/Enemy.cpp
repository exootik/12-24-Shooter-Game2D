#include "Enemy.h"
#include "GameScene.h"
#include "GameManager.h"
#include "InputManager.h"
#include "AssetManager.h"

#include "Projectile.h"
#include "Player.h"

#include <iostream>
#include <cmath>

Enemy::Enemy(float width, float height, int layer, const Color& color, bool hasCollision,Scene* pScene) : Entity(width, height, layer, true, color, pScene)
{
	m_canShootTimerEnemy3 = m_tempTime + 3.0f;
}

Enemy::Enemy(float width, float height, int layer, Scene* pScene) : Entity(width, height, layer, true, Color::Red, pScene)
{
	m_canShootTimerEnemy3 = m_tempTime + 3.0f;
}

void Enemy::OnUpdate()
{
	bool pGameReset = GetScene<GameScene>()->m_gameReset;
	if (pGameReset)
	{
		Destroy();
	}
	GameScene* scene = GetScene<GameScene>();
	int ratio = GetScene<GameScene>()->ratio;

	if (GetLifePoint() <= 0)
	{
		GetScene<GameScene>()->enemyInScene--;
		Player* pPlayer = GetScene<GameScene>()->pPlayer;
		pPlayer->IncrementScore();
		Destroy();
		if (GetTypeOfEnemy() == 41)
		{
			pEnemy41 = CreateEntity<Enemy>(50 * ratio, 50 * ratio, AssetManager::GetSprite("EDrone1").resource, 5);
			GetScene<GameScene>()->enemyInScene++;
			pEnemy41->SetTypeOfEnemy(42);
			pEnemy41->SetPosition(GetPosition().m_x + 50, GetPosition().m_y - 70);
			pEnemy41->SetSpeed(100.0f);
			pEnemy41->SetLifePoint(2);
			pEnemy41->SetTag(GameScene::ENEMY);

			pEnemy41 = CreateEntity<Enemy>(50 * ratio, 50 * ratio, AssetManager::GetSprite("EDrone1").resource, 5);
			GetScene<GameScene>()->enemyInScene++;
			pEnemy41->SetTypeOfEnemy(42);
			pEnemy41->SetPosition(GetPosition().m_x + 50, GetPosition().m_y + 70);
			pEnemy41->SetSpeed(100.0f);
			pEnemy41->SetLifePoint(2);
			pEnemy41->SetTag(GameScene::ENEMY);
		}
		if (GetTypeOfEnemy() == 42)
		{
			pEnemy41 = CreateEntity<Enemy>(30 * ratio, 30 * ratio, AssetManager::GetSprite("EDrone1").resource, 5);
			GetScene<GameScene>()->enemyInScene++;
			pEnemy41->SetTypeOfEnemy(43);
			pEnemy41->SetPosition(GetPosition().m_x + 50, GetPosition().m_y - 40);
			pEnemy41->SetSpeed(100.0f);
			pEnemy41->SetLifePoint(1);
			pEnemy41->SetTag(GameScene::ENEMY);

			pEnemy41 = CreateEntity<Enemy>(30 * ratio, 30 * ratio, AssetManager::GetSprite("EDrone1").resource, 5);
			GetScene<GameScene>()->enemyInScene++;
			pEnemy41->SetTypeOfEnemy(43);
			pEnemy41->SetPosition(GetPosition().m_x + 50, GetPosition().m_y + 40);
			pEnemy41->SetSpeed(100.0f);
			pEnemy41->SetLifePoint(1);
			pEnemy41->SetTag(GameScene::ENEMY);

		}
		if (GetTypeOfEnemy() == 5)
		{
			GetScene<GameScene>()->currentWave = 6;
		}
	}
	// ENEMY 1
	if (GetTypeOfEnemy() == 1)
	{
		SetDirection(m_directionX, 0.0f, GetSpeed());

		if (GetPosition().m_x < (scene->GetWindowWidth() / 100) * 90)
		{
			SetDirection(0.0f, 0.0f, 0.0f);
		}
		Shoot();
	}
	// ENEMY 2
	if (GetTypeOfEnemy() == 2 || GetTypeOfEnemy() == 5)
	{
		SetDirection(m_directionX, m_directionY, GetSpeed());

		if (GetPosition().m_x > scene->GetWindowWidth() * 0.8 && GetPosition().m_x < scene->GetWindowWidth() * 0.95 && GetPosition().m_y > scene->GetWindowHeight() * 0.15 && GetPosition().m_y < scene->GetWindowHeight() * 0.85)
		{
			m_canChangeDirection = true;
		}
		if (GetPosition().m_x < scene->GetWindowWidth() * 0.8 && m_canChangeDirection == true)
		{
			SetDirectionX(-m_directionX);
			m_canChangeDirection = false;
		}
		if (GetPosition().m_x > scene->GetWindowWidth() * 0.95 && m_canChangeDirection == true)
		{
			SetDirectionX(-m_directionX);
			m_canChangeDirection = false;
		}
		if (GetPosition().m_y > scene->GetWindowHeight() * 0.85 && m_canChangeDirection == true)
		{
			SetDirectionY(-m_directionY);
			m_canChangeDirection = false;
		}
		if (GetPosition().m_y < scene->GetWindowHeight() * 0.15 && m_canChangeDirection == true)
		{
			SetDirectionY(-m_directionY);
			m_canChangeDirection = false;
		}
		if (GetPosition().m_y > scene->GetWindowHeight())
		{
			Destroy();
		}
		if (GetPosition().m_y < 0)
		{
			Destroy();
		}
		Shoot();
	}

	// ENEMY 3
	if (GetTypeOfEnemy() == 3)
	{
		Shoot();
	}

	// ENEMY 4
	if (GetTypeOfEnemy() == 41 || GetTypeOfEnemy() == 42 || GetTypeOfEnemy() == 43)
	{
		Player* player = GetScene<GameScene>()->pPlayer;
		GoToPosition(player->GetPosition().m_x, player->GetPosition().m_y, GetSpeed());
	}

	//Boss
	if (GetTypeOfEnemy() == 5)
	{
		Shoot();
	}
}

void Enemy::Shoot()
{
	int ratio = GetScene<GameScene>()->ratio;

	m_tempTime += GetScene<GameScene>()->GetDeltaTime();
	m_canShootTimerBoss += GetScene<GameScene>()->GetDeltaTime();

	if (m_canShootTimerEnemy1 < m_tempTime && GetTypeOfEnemy() != 3)
	{
		pProjectileEnemy = CreateEntity<Projectile>(10 * ratio, 10 * ratio, 5, Color::Blue);
		pProjectileEnemy->SetTag(GameScene::PROJECTILEENEMY);
		pProjectileEnemy->ShootProjectileEnemy1(this);
		m_canShootTimerEnemy1 = m_tempTime + m_cooldownForShootEnemy;
	}
	if (GetTypeOfEnemy() == 3)
	{
		if (m_canShootTimerEnemy3 < m_tempTime && m_canShoot == true)
		{
			pProjectileEnemy = CreateEntity<Projectile>(200 * ratio, GetScene<GameScene>()->GetWindowHeight(), 6, Color::Blue);
			pProjectileEnemy->SetTag(GameScene::PROJECTILEENEMY);
			pProjectileEnemy->ShootProjectileEnemy3Laser(this);
			m_canShoot = false;
		}
		if (m_canShootTimerEnemy3 < m_tempTime - 4.0f)
		{
			Destroy();
			GetScene<GameScene>()->enemyInScene--;
		}
	}
	if (GetTypeOfEnemy() == 5)
	{
		int x = 30;
		int length = 0;
		Enemy* boss = GetScene<GameScene>()->pBoss;

		if (m_canShootTimerBoss > 5.0f && m_canBossShoot == true)
		{
			pProjectileEnemy = CreateEntity<Projectile>(GetScene<GameScene>()->GetWindowWidth(), GetScene<GameScene>()->GetWindowHeight() * 0.15, 6, Color::Brown);
			pProjectileEnemy->SetTag(GameScene::PROJECTILEENEMY);
			
			pProjectileEnemy->ShootProjectileBossLaser(this);
			m_canShootTimerBoss = 0.0f;
			m_canBossShoot = false;
		}

		if (m_canShootTimerBoss > 10.0f &&  m_canBossShoot == false)
		{
			m_canBossShoot = true;
		}
	}
}

void Enemy::OnCollision(Entity* collidedWith)
{
	Projectile* p3 = GetScene<GameScene>()->pProjectile3;
	Player* pPlayer = GetScene<GameScene>()->pPlayer;

	if (collidedWith->IsTag(GameScene::Tag::PROJECTILE) || collidedWith->IsTag(GameScene::Tag::PROJECTILETETECHERCHEUSE))
	{
		if (!p3)
		{
			collidedWith->Destroy();
		}
		m_lifePoint -= 1;
	}
	if (collidedWith->IsTag(GameScene::Tag::ULTIMATE))
	{
		m_lifePoint -= 1;
	}
	if (collidedWith->IsTag(GameScene::Tag::PLAYER))
	{
		m_lifePoint -= 1;
		pPlayer->m_lifePoint -= 1;
	}
}

const std::vector<WaveConfig> waveConfigs =
{
	//enemy1, enemy2, enemy3, enemy4
	{   3,       1,      0,      0,      0}, // Wave 1
	{   5,       3,      1,		 0,      0}, // Wave 2
	{   7,		 5,		 3,		 1,      0}, // Wave 3
	{   10,		 7,		 5,		 3,      0}, // Wave 4
	{   0,		 0,		 0,		 0,      1}, // Wave 5
	{   0,		 0,		 0,		 0,      0}  // Fin de partie
};
