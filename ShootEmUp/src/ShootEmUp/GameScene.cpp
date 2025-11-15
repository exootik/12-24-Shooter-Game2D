#include "GameScene.h"

#include "Player.h"
#include "Enemy.h"
#include "Entity.h"
#include "Projectile.h"
#include "ObstacleDestructible.h"
#include "ObstacleIndestructible.h"
#include "Bonus.h"
#include "InputManager.h"
#include "Background.h"
#include "AssetManager.h"
#include "Debug.h"
#include "Button.h"
#include "Color.h"
#include "AnimationManager.h"

#include <iostream>
#include <random>

void GameScene::LoadAssets()
{
    AssetManager::LoadSpriteSheet("MissileBleu", 6, 3443, 261, 1, 6);
    AssetManager::LoadSpriteSheet("MissileRouge", 6, 3733, 260, 1, 6);
    AssetManager::LoadSpriteSheet("Flamme", 4, 951, 95, 1, 4);

    AnimationManager::CreateAnimation("MissileRouge", "MissileRouge", 0, 6).resource->SetSpeed(0.05f);
    AnimationManager::CreateAnimation("MissileBleu", "MissileBleu", 0, 6).resource->SetSpeed(0.05f);
    AnimationManager::CreateAnimation("Flamme", "Flamme", 0, 4);
}

void GameScene::OnInitialize()
{
    srand(time(nullptr));

    switch (GetWindowHeight())
    {
    case 720:
        ratio = 1;
        break;
    case 1080:
        ratio = 1.5;
        break;
    case 2160:
        ratio = 3;
        break;

    default:
        ratio = 1;
    }

    AssetManager::LoadAtlas("Atlas");

    pBackground1 = CreateEntity<Background1>(GetWindowWidth(), GetWindowHeight(), AssetManager::GetSprite("Town").resource, 0);
    pBackground2 = CreateEntity<Background2>(GetWindowWidth(), GetWindowHeight(), AssetManager::GetSprite("Clouds").resource, 1);
    pBackground3 = CreateEntity<Background3>(GetWindowWidth(), GetWindowHeight(), AssetManager::GetSprite("Birds").resource, 2);
    pBackground4 = CreateEntity<Background4>(GetWindowWidth(), GetWindowHeight(), AssetManager::GetSprite("Road").resource, 3);

	pPlayer = CreateEntity<Player>(60 * ratio, 30 * ratio, AssetManager::GetSprite("Voiture1").resource, 5);
    pPlayer->SetTag(GameScene::PLAYER);
    pPlayer->SetPosition(100.0f, GetWindowHeight() * 0.5);

    pButton = CreateEntity<Button>(400, 200,Color::White,5);
    pButton->SetPosition(GetWindowWidth() * 0.5, GetWindowHeight() * 0.5);
    pButton->SetTypeOfButton(1);

    currentWave++;
    InitializeWave(currentWave);
}

void GameScene::OnEvent(const GCInputSystem* inputsystem)
{
    if (!m_gameInPause)
    {
        //Mouvements
        pPlayer->Movement(inputsystem);

        m_totalTime += GetDeltaTime();

        if (inputsystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::A) && m_canShootTimer1 < m_totalTime)
        {
                pProjectile1 = CreateEntity<Projectile>(10 * ratio, 10 * ratio, Color::Red, 6);
                pProjectile1->SetTag(GameScene::PROJECTILE);
                pProjectile1->PlayAnimation("MissileRouge");
                pProjectile1->SetScale(0.25f,0.25f);

                pProjectile1->ShootProjectile1(pPlayer);

                m_canShootTimer1 = m_totalTime + m_cooldownForShoot;
        }
        if (inputsystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::Z) && m_canShootTimer2 < m_totalTime && pPlayer->m_bulletOfProjectile2 > 0)
        {
            pProjectile2 = CreateEntity<Projectile>(20 * ratio, 20 * ratio,Color::Red, 6);
            pProjectile2->ShootProjectile2(pPlayer);
            pProjectile2->PlayAnimation("MissileBleu");
            pProjectile2->SetScale(0.25f, 0.25f);
            pProjectile2->SetCollisionSize(600.f, 600.f);

            m_canShootTimer2 = m_totalTime + m_cooldownForShoot * 2;

            pPlayer->m_bulletOfProjectile2 -= 2;
        }

        if (inputsystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::E))
        {
            if (!pProjectile3)
            {
                pProjectile3 = CreateEntity<Projectile>(50 * ratio, 50 * ratio, AssetManager::GetSprite("Phares").resource,6);
                pProjectile3->SetTag(GameScene::PROJECTILE);
            }
            pProjectile3->SetPosition(pPlayer->GetPosition().m_x + (pPlayer->GetWidth() * 0.65), pPlayer->GetPosition().m_y);
        }
        if (inputsystem->m_pKeyboard->GetKeyUp(GCKEYBOARD::E))
        {
            pProjectile3->DestroyProjectile3();
            pProjectile3 = nullptr;
        }
        if (inputsystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::R) && m_canDoUltimateTimer < m_totalTime)
        {
            pPlayer->DoUltimate();

            m_canDoUltimateTimer = m_totalTime + m_cooldownForUltimate;
        }
        if (inputsystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::SPACEBAR) && m_canDoBoostSpeedTimer < m_totalTime)
        {
            pPlayer->DoBoostSpeed();

            m_canDoBoostSpeedTimer = m_totalTime + m_cooldownForBoostSpeed;
        }
    }
    
    if (inputsystem->m_pMouse->GetKeyDown(GCMOUSE::LEFT))
    {
        // Condition qui correspond aux coordonn�s des boutons
        if (inputsystem->m_pMouse->GetMousePos().x > GetWindowWidth() * 0.5 - 200
            && inputsystem->m_pMouse->GetMousePos().x < GetWindowWidth() * 0.5 + 200
            && inputsystem->m_pMouse->GetMousePos().y > GetWindowHeight() * 0.5 - 70
            && inputsystem->m_pMouse->GetMousePos().y < GetWindowHeight() * 0.5 + 130)
        {
            if (m_gameInPause = true)
            {
                pButton->Destroy();
                m_gameInPause = false;
                if (m_gameReset == true)
                {
                    m_gameInPause = true;
                    m_gameReset = false;
                    ResetGame();
                }
            }
        }
    }
    if (m_gameInPause == false && inputsystem->m_pKeyboard->GetKeyDown(GCKEYBOARD::ESC))
    {
        m_gameInPause = true;
        pButton = CreateEntity<Button>(400, 200, AssetManager::GetSprite("UIPause").resource, 6);
        pButton->SetPosition(GetWindowWidth() * 0.5, GetWindowHeight() * 0.5);
        pButton->SetTypeOfButton(2);
    }
    if (m_gameInPause == false && inputsystem->m_pKeyboard->GetKeyDown(GCKEYBOARD::ENTER))
    {
        m_gameInPause = false;
        pButton->Destroy();
    }
    if (m_gameInPause == false && inputsystem->m_pKeyboard->GetKeyDown(GCKEYBOARD::M))
    {
        currentWave = 6;
    }
}

void GameScene::UpdateEnemyWave(int waveNumber, int mob1, int mob2, int mob3, int mob4, int boss)
{
    if (enemiesInWave < (mob1 + mob2 + mob3 + mob4 + boss))
    {
        if (m_timeForEnemySpawn1 > 1.5f && (m_mob1 < mob1))
        {
            pEnemy1 = CreateEntity<Enemy>(70 * ratio, 50 * ratio, AssetManager::GetSprite("EMouse").resource, 4);
            pEnemy1->SetTag(GameScene::ENEMY);
            pEnemy1->SetTypeOfEnemy(1);
            pEnemy1->SetPosition(GetWindowWidth() + (50 * ratio), GetRandomPositionY());
            pEnemy1->SetSpeed(100.0f);
            m_timeForEnemySpawn1 = 0.0f;
            enemyInScene++;
            enemiesInWave++;
            m_mob1++;
        }
        
        if (m_timeForEnemySpawn2 > 3.0f && (m_mob2 < mob2))
        {
            pEnemy2 = CreateEntity<Enemy>(70 * ratio, 50 * ratio, AssetManager::GetSprite("EMouse").resource, 4);
            pEnemy2->SetTag(GameScene::ENEMY);
            pEnemy2->SetTypeOfEnemy(2);
            pEnemy2->SetPosition(GetWindowWidth() + (50 * ratio), GetRandomPositionY());
            pEnemy2->SetSpeed(100.0f);
            m_timeForEnemySpawn2 = 0.0f;
            enemyInScene++;
            enemiesInWave++;
            m_mob2++;
        }
        
        if (m_timeForEnemySpawn3 > 5.0f && (m_mob3 < mob3))
        {
            pEnemy3 = CreateEntity<Enemy>(65 * ratio, 50 * ratio, AssetManager::GetSprite("ETank").resource, 4);
            pEnemy3->SetTypeOfEnemy(3);
            pEnemy3->SetPosition(GetRandomPositionX(), 20);
            m_timeForEnemySpawn3 = 0.0f;
            enemyInScene++;
            enemiesInWave++;
            m_mob3++;
        }
        
        if (m_timeForEnemySpawn4 > 3.0f && (m_mob4 < mob4))
        {
            pEnemy4 = CreateEntity<Enemy>(75 * ratio, 65 * ratio, AssetManager::GetSprite("EDrone1").resource, 5);
            pEnemy4->SetTag(GameScene::ENEMY);
            pEnemy4->SetTypeOfEnemy(41);
            pEnemy4->SetPosition(GetWindowWidth() + (70 * ratio), GetRandomPositionY());
            pEnemy4->SetSpeed(100.0f);
            pEnemy4->SetLifePoint(4);
            m_timeForEnemySpawn4 = 0.0f;
            enemyInScene++;
            enemiesInWave++;
            m_mob4++;
        }
        if (m_boss < boss)
        {
            pBoss = CreateEntity<Enemy>(250 * ratio, 250 * ratio, AssetManager::GetSprite("Boss1").resource,5);

            pBoss->SetTag(GameScene::ENEMY);
            pBoss->SetTypeOfEnemy(5);
            pBoss->SetPosition(GetWindowWidth() * 0.9, GetWindowHeight() * 0.5);
            pBoss->SetSpeed(100.0f);
            pBoss->SetLifePoint(10);
            m_boss++;
        }

        if (m_timeForEnemySpawn3 > 10.0f && m_boss == 1)
        {
            pEnemy3 = CreateEntity<Enemy>(65 * ratio, 50 * ratio, AssetManager::GetSprite("ETank").resource,5);
            pEnemy3->SetTag(GameScene::ENEMY);
            pEnemy3->SetTypeOfEnemy(3);
            pEnemy3->SetPosition(GetRandomPositionX(), 20);
            m_timeForEnemySpawn3 = 0.0f;
        }

        if (m_timeForEnemySpawn4 > 5.0f && m_boss == 1)
        {
            pEnemy4 = CreateEntity<Enemy>(75 * ratio, 65 * ratio, AssetManager::GetSprite("EDrone1").resource,5);
            pEnemy4->SetTag(GameScene::ENEMY);
            pEnemy4->SetTypeOfEnemy(41);
            pEnemy4->SetPosition(GetWindowWidth() + (70 * ratio), GetRandomPositionY());
            pEnemy4->SetSpeed(100.0f);
            pEnemy4->SetLifePoint(4);
            m_timeForEnemySpawn4 = 0.0f;
        }
    }
}

void GameScene::OnUpdate()
{

    pPlayer->UpdateSprite();

    static char bufferscoreText[20];
    sprintf_s(bufferscoreText, sizeof(bufferscoreText), "Score : %d", pPlayer->GetScore());
    scoreText = bufferscoreText;
    Debug::CreateText(GetWindowWidth() - 300, 5, scoreText, Color::Red);

    static char bufferlifePointPlayerText[20];
    sprintf_s(bufferlifePointPlayerText, sizeof(bufferlifePointPlayerText), "Vie : %d", pPlayer->m_lifePoint);
    lifePointPlayerText = bufferlifePointPlayerText;
    Debug::CreateText(30, 5, lifePointPlayerText, Color::Red);

    static char bufferlifeBulletText[20];
    sprintf_s(bufferlifeBulletText, sizeof(bufferlifeBulletText), "Munition : %d", pPlayer->m_bulletOfProjectile2);
    bulletPlayerText = bufferlifeBulletText;
    Debug::CreateText(GetWindowWidth() * 0.5 - 100 , 5, bulletPlayerText, Color::Red);

    if (currentWave < 3)
    {
        Debug::CreateText(GetWindowWidth() * 0.25, GetWindowHeight() - 150, "Tirs : A, Z, E, R", Color::Red);
        Debug::CreateText(GetWindowWidth() * 0.5, GetWindowHeight() - 150, "Deplacements : Fleches directionnelles", Color::Red);
    }
   
    if (m_gameInPause)
    {
        GetGameManager()->PauseGame(true);
    }
    if (!m_gameInPause)
    {
        GetGameManager()->PauseGame(false);
    }
    if (pPlayer->m_lifePoint < 1 && m_gameReset == false)
    {
        m_gameReset = true;
        m_gameInPause = true;
        pButton = CreateEntity<Button>(400 * ratio, 200* ratio, AssetManager::GetSprite("UIGameOver").resource ,6);
        pButton->SetPosition(GetWindowWidth() * 0.5, GetWindowHeight() * 0.5);
        pButton->SetTypeOfButton(3);
    }   
    if (currentWave > 5 && m_gameReset == false)
    {
        m_gameReset = true;
        m_gameInPause = true;
        pButton = CreateEntity<Button>(400 * ratio, 200 * ratio, AssetManager::GetSprite("UIWin").resource, 6);
        pButton->SetPosition(GetWindowWidth() * 0.5, GetWindowHeight() * 0.5);
        pButton->SetTypeOfButton(4);
    }
    m_totalTimeOfGame += GetDeltaTime();

    m_timeForEnemySpawn1 += GetDeltaTime();
    m_timeForEnemySpawn2 += GetDeltaTime();
    m_timeForEnemySpawn3 += GetDeltaTime();
    m_timeForEnemySpawn4 += GetDeltaTime();

    if (currentWave > 0 && currentWave <= waveConfigs.size())
    {
        const WaveConfig& config = waveConfigs[currentWave - 1];
        UpdateEnemyWave(currentWave, config.mob1, config.mob2, config.mob3, config.mob4, config.boss);
    }
    else
    {
        std::cerr << "waveNumber out of range: " << currentWave << std::endl;
    }

    if (CanNextWave())
    {
        currentWave++;

        InitializeWave(currentWave);
    }

    // GESTION OBTACLE
    m_timeForObstacleDestructibleSpawn += GetDeltaTime();
    m_timeForObstacleIndestructibleSpawn += GetDeltaTime();

    if (m_timeForObstacleDestructibleSpawn > 2.0f)
    {
        pObstacleDestructible = CreateEntity<ObstacleDestructible>(70 * ratio, 70 * ratio, AssetManager::GetSprite("Travaux").resource, 4);
        pObstacleDestructible->SetScale(0.5f, 0.5f);
        pObstacleDestructible->SetTag(GameScene::OBSTACLE);
        pObstacleDestructible->SetPosition(GetWindowWidth() + (70 * ratio), GetRandomPositionY());
        pObstacleDestructible->SetSpeed(300.0f);
        pObstacleDestructible->SetDirection(-1, 0, pObstacleDestructible->GetSpeed());
        m_timeForObstacleDestructibleSpawn = 0.0f;
    }
    if (m_timeForObstacleIndestructibleSpawn > 5.0f)
    {
        pObstacleIndestructible = CreateEntity<ObstacleIndestructible>(70 * ratio, 70 * ratio, AssetManager::GetSprite("Trou").resource, 4);
        pObstacleIndestructible->SetScale(0.3f, 0.3f);
        pObstacleIndestructible->SetTag(GameScene::OBSTACLE);
        pObstacleIndestructible->SetPosition(GetWindowWidth() + (70 * ratio), GetRandomPositionY());
        pObstacleIndestructible->SetSpeed(300.0f);
        pObstacleIndestructible->SetDirection(-1, 0, pObstacleIndestructible->GetSpeed());
        m_timeForObstacleIndestructibleSpawn = 0.0f;
    }

    // GESTION BONUS
    m_timeForBonusSpawn += GetDeltaTime();

    if (m_timeForBonusSpawn > m_cooldownForBonusSpawn)
    {
        pBonus = CreateEntity<Bonus>(70 * ratio, 70 * ratio, AssetManager::GetSprite("Caisse").resource, 4);
        pBonus->SetScale(0.25f, 0.25f);
        pBonus->SetTag(GameScene::BONUS);

        pBonus->SetPosition(GetRandomPositionX(), GetRandomPositionY());
        m_timeForBonusSpawn = 0.0f;
    }
}

int GameScene::GetRandomPositionY()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(GetWindowHeight() * 0.20, GetWindowHeight() * 0.80);

    return dist(gen);
}

int GameScene::GetRandomPositionX()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(GetWindowWidth() * 0.1, GetWindowWidth() * 0.6);

    return dist(gen);
}

void GameScene::InitializeWave(int waveNumber)
{
    if (waveNumber > 0 && waveNumber <= waveConfigs.size())
    {
        const WaveConfig& config = waveConfigs[waveNumber - 1];
        UpdateEnemyWave(waveNumber, config.mob1, config.mob2, config.mob3, config.mob4, config.boss);
    }
    else
    {
        std::cerr << "waveNumber out of range: " << waveNumber << std::endl;
    }
}

bool GameScene::CanNextWave()
{
    if (enemyInScene > 0)
    {
        return false;
    }
    if (enemyInScene == 0)
    {
        m_timeOfLastWave += GetDeltaTime();
    }
    if (m_timeOfLastWave >= 5.0f)
    {
        enemiesInWave = 0;
        m_mob1 = 0;
        m_mob2 = 0;
        m_mob3 = 0;
        m_mob4 = 0;
        m_timeOfLastWave = 0.0f;
        return true;
    }
    return false;
}

void GameScene::ResetGame()
{
    pPlayer->SetPosition(100.0f, GetWindowHeight() * 0.5);
    pPlayer->resetScore();
    pPlayer->m_lifePoint = pPlayer->m_maxLifePoint;
    pPlayer->m_bulletOfProjectile2 = pPlayer->m_maxBulletOfProjectile2;

    m_totalTimeOfGame = 0.0f;
    m_totalTime = 0.0f;
    m_timeOfLastWave = 0.0f;

    m_timeForEnemySpawn1 = 0.0f;
    m_timeForEnemySpawn2 = 0.0f;
    m_timeForEnemySpawn3 = 0.0f;
    m_timeForEnemySpawn4 = 0.0f;
    m_timeForObstacleDestructibleSpawn = 0.0f;
    m_timeForObstacleIndestructibleSpawn = 0.0f;

    m_canDoBoostSpeedTimer = 10.0f;
    m_canDoUltimateTimer = 5.0f;
    m_canShootTimer1 = 0.0f;
    m_canShootTimer2 = 0.0f;
    m_canShootTimer3 = 0.0f;
    m_timeForBonusSpawn = 0.0f;

    currentWave = 0;
    enemyInScene = 0;
    enemiesInWave = 0;
    m_mob1 = 0;
    m_mob2 = 0;
    m_mob3 = 0;
    m_mob4 = 0;
    m_boss = 0;

    srand(time(nullptr));

    pButton = CreateEntity<Button>(400 * ratio, 200 * ratio, Color::White,6);
    pButton->SetPosition(GetWindowWidth() * 0.5, GetWindowHeight() * 0.5);
    pButton->SetTypeOfButton(1);

    pProjectile3 = nullptr;

    currentWave++;
    InitializeWave(currentWave);
}