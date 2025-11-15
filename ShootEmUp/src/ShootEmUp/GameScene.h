#pragma once

#include "GameManager.h"
#include "AssetManager.h"
#include "Scene.h"
#include "Entity.h"
#include <vector>

class Player;
class Projectile;

class Enemy;

class ObstacleDestructible;
class ObstacleIndestructible;

class Background1;
class Background2;
class Background3;
class Background4;

class Bonus;
class Button;

struct WaveConfig 
{
	int mob1;
	int mob2;
	int mob3;
	int mob4;
	int boss;
};

extern const std::vector<WaveConfig> waveConfigs;

class GameScene : public Scene
{
public:
	Player* pPlayer;

	Enemy* pEnemy1;
	Enemy* pEnemy2;
	Enemy* pEnemy3;
	Enemy* pEnemy4;
	Enemy* pBoss;

	Projectile* pProjectile1;
	Projectile* pProjectile2;
	Projectile* pProjectile3;

	ObstacleDestructible* pObstacleDestructible;
	ObstacleIndestructible* pObstacleIndestructible;

	Background1* pBackground1;
	Background2* pBackground2;
	Background3* pBackground3;
	Background4* pBackground4;

	Bonus* pBonus;
	Button* pButton;

	enum Tag
	{
		PLAYER,
		ENEMY,
		PROJECTILE,
		PROJECTILETETECHERCHEUSE,
		PROJECTILEENEMY,
		PROJECTILEINNACTIF,
		ULTIMATE,
		OBSTACLE,
		OBSTACLEINNACTIF,
		BONUS,
	};

public:
	void LoadAssets() override;
	void OnInitialize() override;
	void OnEvent(const GCInputSystem* inputsystem) override;
	void OnUpdate() override;
	void OnFixedUpdate() override {};

	void InitializeWave(int waveNumber);
	bool CanNextWave();
	void UpdateEnemyWave(int waveNumber, int mob1, int mob2, int mob3, int mob4, int boss);

	void ResetGame();

	int GetRandomPositionY();
	int GetRandomPositionX();

	int width;
	int height;
	int ratio;

	float m_totalTimeOfGame = 0.0f;
	float m_totalTime = 0.0f;
	float m_timeOfLastWave = 0.0f;

	float m_timeForEnemySpawn1 = 0.0f;
	float m_timeForEnemySpawn2 = 0.0f;
	float m_timeForEnemySpawn3 = 0.0f;
	float m_timeForEnemySpawn4 = 0.0f;

	float m_canDoBoostSpeedTimer = 10.0f;
	float m_canDoUltimateTimer = 15.0f;
	float m_canShootTimer1 = 0.0f;
	float m_canShootTimer2 = 0.0f;
	float m_canShootTimer3 = 0.0f;
	float m_timeForBonusSpawn = 0.0f;

	float m_cooldownForBoostSpeed = 10.0f;
	float m_cooldownForUltimate = 15.0f;
	float m_cooldownForShoot = 1.0f;
	float m_cooldownForBonusSpawn = 7.0f;

	int currentWave = 0;
	int enemyInScene = 0;
	int enemiesInWave = 0;
	int m_mob1 = 0;
	int m_mob2 = 0;
	int m_mob3 = 0;
	int m_mob4 = 0;
	int m_boss = 0;

	float m_timeForObstacleDestructibleSpawn = 0.0f;
	float m_timeForObstacleIndestructibleSpawn = 0.0f;

	const char* scoreText;
	const char* lifePointPlayerText;
	const char* bulletPlayerText;

	bool m_gameInPause = true;
	bool m_gameReset = false;
};